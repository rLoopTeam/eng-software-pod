Namespace SIL3.rLoop.rPodControl.Panels.Settings

    ''' <summary>
    ''' Network settings
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Network
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        ''The grid control
        Private m_pSG As SIL3.ApplicationSupport.SandGrid.Grid

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String)
            MyBase.New(sPanelText)

        End Sub
#End Region '#Region "NEW"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Me.m_pSG = New SIL3.ApplicationSupport.SandGrid.Grid(Me.m_pInnerPanel, False)

            Me.m_pSG.Column__Add("\",
                                 New String() {"MODULE", "IP ADDX", "PORT", "MAC"},
                                 New String() {"", "kIP", "kPORT", "kMAC"},
                                 New Integer() {180, 180, 120, 120},
                                 New Boolean() {False, True, True, True})

            'add some settings
            Me.m_pSG.Row__Add("\", New String() {"Flight Control", "192.168.0.100", "9100", "00: 26:80:01:00:00"})
            Me.m_pSG.Row__Add("\", New String() {"Power Fwd", "192.168.0.110", "9110", "00: 26:80:01:00:01"})
            Me.m_pSG.Row__Add("\", New String() {"Power Aft", "192.168.0.111", "9111", "00: 26:80:01:00:02"})
            Me.m_pSG.Row__Add("\", New String() {"Landing Gear", "192.168.0.120", "9120", "00: 26:80:01:00:03"})
            Me.m_pSG.Row__Add("\", New String() {"Gimbal Control", "192.168.0.130", "9130", "00: 26:80:01:00:04"})

            'todo: load from a file in the future

        End Sub
#End Region '#Region "PANEL LAYOUT"

    End Class


End Namespace
