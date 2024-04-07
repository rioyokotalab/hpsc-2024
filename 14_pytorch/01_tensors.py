import torch

epochs = 300
batch_size = 32
D_in = 784
H = 100
D_out = 10
learning_rate = 1.0e-06

# create random input and output data
x = torch.randn(batch_size, D_in)
y = torch.randn(batch_size, D_out)

# randomly initialize weights
w1 = torch.randn(D_in, H)
w2 = torch.randn(H, D_out)

for epoch in range(epochs):
    # forward pass: compute predicted y
    h = x.mm(w1)
    h_r = h.clamp(min=0)
    y_p = h_r.mm(w2)

    # compute and print loss
    loss = (y_p - y).pow(2).sum().item()
    print(epoch, loss)

    # backward pass: compute gradients of loss with respect to w2
    grad_y_p = 2.0 * (y_p - y)
    grad_w2 = h_r.t().mm(grad_y_p)

    # backward pass: compute gradients of loss with respect to w1
    grad_h_r = grad_y_p.mm(w2.t())
    grad_h = grad_h_r.clone()
    grad_h[h < 0] = 0
    grad_w1 = x.t().mm(grad_h)

    # update weights
    w1 -= learning_rate * grad_w1
    w2 -= learning_rate * grad_w2
