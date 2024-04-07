import torch
import torch.distributed as dist
import torch.nn as nn
import torch.nn.functional as F
from torchvision import datasets, transforms, models
from torch.nn.parallel import DistributedDataParallel as DDP
import time
import os

def print0(message):
    if dist.is_initialized():
        if dist.get_rank() == 0:
            print(message, flush=True)
    else:
        print(message, flush=True)

def train(train_loader,model,criterion,optimizer,epoch,device,world_size):
    model.train()
    t = time.perf_counter()
    for batch_idx, (data, target) in enumerate(train_loader):
        data = data.to(device)
        target = target.to(device)
        output = model(data)
        loss = criterion(output, target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if batch_idx % (200 / world_size) == 0:
            print0('Train Epoch: {} [{:>5}/{} ({:.0%})]\tLoss: {:.6f}\t Time:{:.4f}'.format(
                epoch, batch_idx * len(data) * world_size, len(train_loader.dataset),
                batch_idx / len(train_loader), loss.data.item(),
                time.perf_counter() - t))
            t = time.perf_counter()

def validate(val_loader,model,criterion,device):
    model.eval()
    val_loss, val_acc = 0, 0
    for data, target in val_loader:
        data = data.to(device)
        target = target.to(device)
        output = model(data)
        loss = criterion(output, target)
        val_loss += loss.item()
        pred = output.data.max(1)[1]
        val_acc += 100. * pred.eq(target.data).cpu().sum() / target.size(0)

    val_loss /= len(val_loader)
    val_acc /= len(val_loader)
    print0('\nValidation set: Average loss: {:.4f}, Accuracy: {:.1f}%\n'.format(
        val_loss, val_acc))

def main():
    master_addr = os.getenv("MASTER_ADDR", default="localhost")
    master_port = os.getenv('MASTER_PORT', default='8888')
    method = "tcp://{}:{}".format(master_addr, master_port)
    rank = int(os.getenv('OMPI_COMM_WORLD_RANK', '0'))
    world_size = int(os.getenv('OMPI_COMM_WORLD_SIZE', '1'))
    dist.init_process_group("nccl", init_method=method, rank=rank, world_size=world_size)
    ngpus = torch.cuda.device_count()
    device = torch.device('cuda',rank % ngpus)

    epochs = 10
    batch_size = 32
    learning_rate = 1.0e-02

    train_dataset = datasets.CIFAR10('./data',
                                     train=True,
                                     download=True,
                                     transform=transforms.ToTensor())
    val_dataset = datasets.CIFAR10('./data',
                                   train=False,
                                   transform=transforms.ToTensor())
    train_sampler = torch.utils.data.distributed.DistributedSampler(
        train_dataset,
        num_replicas=dist.get_world_size(),
        rank=dist.get_rank())
    train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                               batch_size=batch_size,
                                               sampler=train_sampler)
    val_loader = torch.utils.data.DataLoader(dataset=val_dataset,
                                             batch_size=batch_size,
                                             shuffle=False)
    model = models.resnet18().to(device)
    model = DDP(model, device_ids=[rank % ngpus])
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

    for epoch in range(epochs):
        model.train()
        train(train_loader,model,criterion,optimizer,epoch,device,world_size)
        validate(val_loader,model,criterion,device)

    dist.destroy_process_group()

if __name__ == '__main__':
    main()
