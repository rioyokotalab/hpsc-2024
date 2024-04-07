import torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision import datasets, transforms
import time

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

epochs = 10
batch_size = 32
D_in = 784
H = 100
D_out = 10
learning_rate = 1.0e-02

# read input data and labels
train_dataset = datasets.MNIST('./data', 
                               train=True, 
                               download=True, 
                               transform=transforms.ToTensor())

train_loader = torch.utils.data.DataLoader(dataset=train_dataset, 
                                           batch_size=batch_size, 
                                           shuffle=True)

# define model
model = TwoLayerNet(D_in, H, D_out)

# define loss function
criterion = nn.CrossEntropyLoss()

# define optimizer
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

lossv, accv = [], []
for epoch in range(epochs):
    # Set model to training mode
    model.train()

    t = time.perf_counter()
    # Loop over each batch from the training set
    for batch_idx, (x, y) in enumerate(train_loader):
        # forward pass: compute predicted y
        y_p = model(x)

        # compute loss
        loss = criterion(y_p, y)

        # backward pass
        optimizer.zero_grad()
        loss.backward()

        # update weights
        optimizer.step()

        if batch_idx % 200 == 0:
            print('Train Epoch: {} [{:>5}/{} ({:.0%})]\tLoss: {:.6f}\t Time:{:.4f}'.format(
                epoch, batch_idx * len(x), len(train_loader.dataset),
                batch_idx / len(train_loader), loss.data.item(),
                time.perf_counter() - t))
            t = time.perf_counter()
