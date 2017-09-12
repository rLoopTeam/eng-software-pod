import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.Drawing')

from System.Windows.Forms import Application

import globals
globals.modbus = modbus

import VehicleConfigurationForm
import CommandSourceForm
import BasicMotorSetupForm
import AssistSettingForm
import FeatureBitsSetting

Application.EnableVisualStyles()

form = BasicMotorSetupForm.BasicMotorSetUpForm()
Application.Run(form)

form = CommandSourceForm.CommandSourceForm()
Application.Run(form)

form = VehicleConfigurationForm.VehicleConfigurationForm()
Application.Run(form)

form = AssistSettingForm.AssistSettingForm()
Application.Run(form)

form = FeatureBitsSetting.FeaturesAddingForm()
Application.Run(form)