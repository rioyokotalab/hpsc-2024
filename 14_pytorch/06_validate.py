import torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision import datasets, transforms
import time

D_in = 784
H = 100
D_out = 10

class TwoLayerNet(nn.Module):
    def __init__(self, D_in, H, D_out):
        super(TwoLayerNet, self).__init__()
        self.fc1 = nn.Linear(D_in, H)
        self.fc2 = nn.Linear(H, D_out)

    def forward(self, x):
        x = x.view(-1, D_in)
        h = self.fc1(x)
        h_r = F.relu(h)
        y_p = self.fc2(h_r)
        return F.log_softmax(y_p, dim=1)


def train(train_loader,model,criterion,optimizer,epoch):
    model.train()
    t = time.perf_counter()
    for batch_idx, (data, target) in enumerate(train_loader):
        output = model(data)
        loss = criterion(output, target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if batch_idx % 200 == 0:
            print('Train Epoch: {} [{:>5}/{} ({:.0%})]\tLoss: {:.6f}\t Time:{:.4f}'.format(
                epoch, batch_idx * len(data), len(train_loader.dataset),
                batch_idx / len(train_loader), loss.data.item(),
                time.perf_counter() - t))
            t = time.perf_counter()

def validate(val_loader,model,criterion):
    model.eval()
    val_loss, val_acc = 0, 0
    for data, target in val_loader:
        output = model(data)
        loss = criterion(output, target)
        val_loss += loss.item()
        pred = output.data.max(1)[1]
        val_acc += 100. * pred.eq(target.data).cpu().sum() / target.size(0)

    val_loss /= len(val_loader)
    val_acc /= len(val_loader)
    print('\nValidation set: Average loss: {:.4f}, Accuracy: {:.1f}%\n'.format(
        val_loss, val_acc))

def main():
    epochs = 10
    batch_size = 32
    learning_rate = 1.0e-02

    train_dataset = datasets.MNIST('./data', 
                                   train=True, 
                                   download=True, 
                                   transform=transforms.ToTensor())
    val_dataset = datasets.MNIST('./data', 
                                 train=False, 
                                 transform=transforms.ToTensor())
    train_loader = torch.utils.data.DataLoader(dataset=train_dataset, 
                                               batch_size=batch_size, 
                                               shuffle=True)
    val_loader = torch.utils.data.DataLoader(dataset=val_dataset, 
                                             batch_size=batch_size, 
                                             shuffle=False)

    model = TwoLayerNet(D_in, H, D_out)
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

    for epoch in range(epochs):
        model.train()
        train(train_loader,model,criterion,optimizer,epoch)
        validate(val_loader,model,criterion)

if __name__ == '__main__':
    main()
