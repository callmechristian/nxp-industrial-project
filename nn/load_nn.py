import torch


'''
Find the final model trained by Unity:

After running the training process, the model is saved in the directory:
    "ml-agents/results/runid"


'''

# load the model trained through untiy
path = "./3DBall-500513.pt"
model = torch.load(path)

print(model)
