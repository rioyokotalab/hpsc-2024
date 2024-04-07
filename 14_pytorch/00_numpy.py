import numpy as np

epochs = 300
batch_size = 32
D_in = 784
H = 100
D_out = 10
learning_rate = 1.0e-06

# create random input and output data
x = np.random.randn(batch_size, D_in)
y = np.random.randn(batch_size, D_out)

# randomly initialize weights
w1 = np.random.randn(D_in, H)
w2 = np.random.randn(H, D_out)

for epoch in range(epochs):
    # forward pass
    h = x.dot(w1) # h = x * w1
    h_r = np.maximum(h, 0) # h_r = ReLU(h)
    y_p = h_r.dot(w2) # y_p = h_r * w2

    # compute mean squared error and print loss
    loss = np.square(y_p - y).sum()
    print(epoch, loss)

    # backward pass: compute gradients of loss with respect to w2
    grad_y_p = 2.0 * (y_p - y)
    grad_w2 = h_r.T.dot(grad_y_p)

    # backward pass: compute gradients of loss with respect to w1
    grad_h_r = grad_y_p.dot(w2.T)
    grad_h = grad_h_r.copy()
    grad_h[h < 0] = 0
    grad_w1 = x.T.dot(grad_h)

    # update weights
    w1 -= learning_rate * grad_w1
    w2 -= learning_rate * grad_w2
