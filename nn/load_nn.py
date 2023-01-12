import torch


'''
Find the final model trained by Unity:

After running the training process, the model is saved in the directory:
    "ml-agents/results/<runid>/<model_name>/<model_name>_<#training_steps>.pt"


Load the model from traning results directory and then you get the PyTorch model

'''

# load the model trained through untiy
path = "./3DBall-500513.pt"
model = torch.load(path)

print(model)
