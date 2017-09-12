import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.Drawing')

import globals
globals.modbus = modbus

from System.Windows.Forms import Application
import FeatureBitsSetting

Application.EnableVisualStyles()


form = FeatureBitsSetting.FeaturesAddingForm()
Application.Run(form)

