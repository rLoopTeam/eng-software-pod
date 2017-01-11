Namespace SIL3.rLoop.rPodControl.Panels.Settings

    ''' <summary>
    ''' Network settings
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Network
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"
        ''' <summary>
        ''' The XYZ Controller network interface
        ''' </summary>
        ''' <remarks></remarks>
        'Private m_pXYZ_Network As LockieInnovation.CNCMachine.Network.XYZ_Network



        ''' <summary>
        ''' Network data log
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pLog As SIL3.ApplicationSupport.LoggingBox

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

            Dim ppT As New Panel
            With ppT
                .Dock = DockStyle.Top
                .Size = New Size(400, 500)
            End With

            Dim ppB As New Panel
            With ppB
                .Dock = DockStyle.Fill
            End With

            MyBase.m_pInnerPanel.Controls.Add(ppB)
            MyBase.m_pInnerPanel.Controls.Add(ppT)

            'Dim btnUP As New LockieInnovation.ApplicationSupport.ButtonHelper(10, 20, 200, "XYZ Update Firmware", ppB, AddressOf Me.btnXYZ__UpdateFirmware__Click)


            'Dim btnUP2 As New LockieInnovation.ApplicationSupport.ButtonHelper(200, "PNP Update Firmware", AddressOf Me.btnPNPHEAD__UpdateFirmware__Click)
            'btnUP2.Layout__BelowControl(btnUP)

            'create the logging box
            Me.m_pLog = New SIL3.ApplicationSupport.LoggingBox(ppT)


        End Sub
#End Region '#Region "PANEL LAYOUT"

    End Class


End Namespace
