import torch
import torch.nn as nn
import torch.nn.functional as F

class TwoLayerNet(nn.Module):
    def __init__(self, D_in, H, D_out):
        super(TwoLayerNet, self).__init__()
        self.fc1 = nn.Linear(D_in, H)
        self.fc2 = nn.Linear(H, D_out)

    def forward(self, x):
        h = self.fc1(x)
        h_r = F.relu(h)
        y_p = self.fc2(h_r)
        return y_p

epochs = 300
batch_size = 32
D_in = 784
H = 100
D_out = 10
learning_rate = 1.0e-04

# create random input and output data
x = torch.randn(batch_size, D_in)
y = torch.randn(batch_size, D_out)

# define model
model = TwoLayerNet(D_in, H, D_out)

# define loss function
criterion = torch.nn.MSELoss(reduction='sum')

# define optimizer
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

for epoch in range(epochs):
    # forward pass: compute predicted y
    y_p = model(x)

    # compute and print loss
    loss = criterion(y_p, y)
    print(epoch, loss.item())

    # backward pass
    optimizer.zero_grad()
    loss.backward()

    # update weights
    optimizer.step()
