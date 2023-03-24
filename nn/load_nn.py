'''
Find the final model trained by Unity:

After running the training process, the model is saved in the directory:
    "ml-agents/results/<runid>/<model_name>/<model_name>_<#training_steps>.pt"


Load the model from traning results directory and then you get the PyTorch model


'''

import torch
from torch import nn
from torchsummary import summary

class ModelClass(nn.Module):
    def __init__(self):
        super(ModelClass, self).__init__()
        

# load the model trained through untiy
PATH = "./trained_models/CarControllerAgent-254474.pt"
model = ModelClass()
model.load_state_dict(torch.load(PATH))

print(model)
