import os
import torch
import torch.distributed as dist

master_addr = os.getenv("MASTER_ADDR", default="localhost")
master_port = os.getenv('MASTER_PORT', default='8888')
method = "tcp://{}:{}".format(master_addr, master_port)
rank = int(os.getenv('OMPI_COMM_WORLD_RANK', '0'))
world_size = int(os.getenv('OMPI_COMM_WORLD_SIZE', '1'))
dist.init_process_group("nccl", init_method=method, rank=rank, world_size=world_size)
print('Rank: {}, Size: {}, Host: {}'.format(dist.get_rank(), dist.get_world_size(), master_addr))

ngpus = torch.cuda.device_count()
device = rank % ngpus
x = torch.randn(1).to(device)
print('rank {}: {}'.format(rank, x))
dist.broadcast(x, src=0)
print('rank {}: {}'.format(rank, x))
dist.destroy_process_group()
