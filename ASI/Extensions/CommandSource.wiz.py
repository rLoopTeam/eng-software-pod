import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.Drawing')

import globals
globals.modbus = modbus

from System.Windows.Forms import Application
import CommandSourceForm

Application.EnableVisualStyles()


form = CommandSourceForm.CommandSourceForm()
Application.Run(form)

