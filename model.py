import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision.models as models


class SingleOutputModel(nn.Module):
    def __init__(self, n_cpu_classes):
        super().__init__()
        self.base_model = models.mobilenet_v2().features # take the model without classifier
        last_channel = models.mobilenet_v2().last_channel # size of the layer before classifier
        # the input for the classifier should be two-dimensional, but we will have
        # [batch_size, channels, width, height]
        # so, let's do the spatial averaging: reduce width and height to 1
        self.pool = nn.AdaptiveAvgPool2d((1, 1))

        # create separate classifiers for our outputs
        self.cpuAct = nn.Sequential(
            nn.Dropout(p=0.2),
            nn.Linear(in_features=last_channel, out_features=n_cpu_classes)
        )

    def forward(self, x):
        x = self.base_model(x)
        x = self.pool(x)

        # reshape from [batch, channels, 1, 1] to [batch, channels] to put it into classifier
        x = torch.flatten(x, 1)

        return {
            'cpuAct': self.cpuAct(x)
        }

    def get_loss(self, net_output, ground_truth):
        cpuAct_loss = F.cross_entropy(net_output['cpuAct'], ground_truth['cpu_act_labels'])

        loss = cpuAct_loss
        return loss, {'cpuAct': cpuAct_loss}