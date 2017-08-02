Namespace SIL3.rLoop.rPodControl.Panels.Gimbal

    ''' <summary>
    ''' Manual Gimbal Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Manual
        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        Private m_txtFaultFlags As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLeftRetract As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLeftExtend As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtRightRetract As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRightExtend As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtLeftState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRightState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

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

#Region "EVENTS"
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags", Me.m_pInnerPanel)
            Me.m_txtFaultFlags = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l1)

            Dim l2a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Left Clutch", Me.m_txtFaultFlags)

            Dim btnClutchL_Disengage As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Disengage", AddressOf Me.btnClutchL_Disengage)
            btnClutchL_Disengage.Layout__BelowControl(l2a)

            Dim btnClutchL_Engage As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Engage", AddressOf Me.btnClutchL_Engage)
            btnClutchL_Engage.Layout__RightOfControl(btnClutchL_Disengage)


            Dim l20a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(300, l2a.Location.Y, "Right Clutch", Me.m_pInnerPanel)
            Dim btnClutchR_Disengage As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Disengage", AddressOf Me.btnClutchR_Disengage)
            btnClutchR_Disengage.Layout__BelowControl(l20a)

            Dim btnClutchR_Engage As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Engage", AddressOf Me.btnClutchR_Engage)
            btnClutchR_Engage.Layout__RightOfControl(btnClutchR_Disengage)


            Dim l3a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Left Directon", btnClutchL_Disengage)
            Dim btnMotorL_DirR As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Reverse", AddressOf Me.btnMotorL_Reverse)
            btnMotorL_DirR.Layout__BelowControl(l3a)

            Dim btnMotorL_DirF As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Forward", AddressOf Me.btnMotorL_Forward)
            btnMotorL_DirF.Layout__RightOfControl(btnMotorL_DirR)


            Dim l30a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Right Directon", btnClutchR_Disengage)
            Dim btnMotorR_DirR As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Reverse", AddressOf Me.btnMotorR_Reverse)
            btnMotorR_DirR.Layout__BelowControl(l30a)

            Dim btnMotorR_DirF As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Forward", AddressOf Me.btnMotorR_Forward)
            btnMotorR_DirF.Layout__RightOfControl(btnMotorR_DirR)


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        Private Sub btnClutchL_Disengage(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_CLUTCH__MANUAL,
                                                 &H11223344L,
                                                 0, 0, 0)

        End Sub

        Private Sub btnClutchL_Engage(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_CLUTCH__MANUAL,
                                                 &H11223344L,
                                                 0, 1, 0)

        End Sub

        Private Sub btnClutchR_Disengage(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_CLUTCH__MANUAL,
                                                 &H11223344L,
                                                 1, 0, 0)

        End Sub

        Private Sub btnClutchR_Engage(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_CLUTCH__MANUAL,
                                                 &H11223344L,
                                                1, 1, 0)

        End Sub


        Private Sub btnMotorL_Reverse(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__DIRECTION_MANUAL,
                                                 &H11223377L,
                                                 0, 0, 0)

        End Sub

        Private Sub btnMotorL_Forward(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__DIRECTION_MANUAL,
                                                 &H11223377L,
                                                0, 1, 0)
        End Sub


        Private Sub btnMotorR_Reverse(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__DIRECTION_MANUAL,
                                                 &H11223377L,
                                                 1, 0, 0)

        End Sub

        Private Sub btnMotorR_Forward(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__DIRECTION_MANUAL,
                                                 &H11223377L,
                                                1, 1, 0)

        End Sub


#End Region '#Region "BUTTON"

    End Class


End Namespace
