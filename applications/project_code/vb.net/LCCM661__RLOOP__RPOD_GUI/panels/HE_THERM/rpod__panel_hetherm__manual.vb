Namespace SIL3.rLoop.rPodControl.Panels.HETherm

    ''' <summary>
    ''' Manual HETherm Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Manual
	        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        Private m_txtFaultFlags As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLeftRetract As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLeftExtend As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtRightRetract As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRightExtend As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtLeftState As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRightState As SIL3.ApplicationSupport.TextBoxHelper

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

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags", Me.m_pInnerPanel)
            Me.m_txtFaultFlags = New SIL3.ApplicationSupport.TextBoxHelper(100, l1)

            Dim l2a As New SIL3.ApplicationSupport.LabelHelper("Solenoid 0", Me.m_txtFaultFlags)
            Dim btnSolOpen_0 As New SIL3.ApplicationSupport.ButtonHelper(100, "Open", AddressOf Me.btnSolOpen_0)
            btnSolOpen_0.Layout__BelowControl(l2a)

            Dim btnSolClose_0 As New SIL3.ApplicationSupport.ButtonHelper(100, "Close", AddressOf Me.btnSolClose_0)
            btnSolClose_0.Layout__RightOfControl(btnSolOpen_0)

            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Solenoid 1", btnSolOpen_0)
            Dim btnSolOpen_1 As New SIL3.ApplicationSupport.ButtonHelper(100, "Open", AddressOf Me.btnSolOpen_1)
            btnSolOpen_1.Layout__BelowControl(l3)
            Dim btnSolClose_1 As New SIL3.ApplicationSupport.ButtonHelper(100, "Close", AddressOf Me.btnSolClose_1)
            btnSolClose_1.Layout__RightOfControl(btnSolOpen_1)

            Dim l4 As New SIL3.ApplicationSupport.LabelHelper("Solenoid 2", btnSolOpen_1)
            Dim btnSolOpen_2 As New SIL3.ApplicationSupport.ButtonHelper(100, "Open", AddressOf Me.btnSolOpen_2)
            btnSolOpen_2.Layout__BelowControl(l4)
            Dim btnSolClose_2 As New SIL3.ApplicationSupport.ButtonHelper(100, "Close", AddressOf Me.btnSolClose_2)
            btnSolClose_2.Layout__RightOfControl(btnSolOpen_2)

            Dim l5 As New SIL3.ApplicationSupport.LabelHelper("Solenoid 3", btnSolOpen_2)
            Dim btnSolOpen_3 As New SIL3.ApplicationSupport.ButtonHelper(100, "Open", AddressOf Me.btnSolOpen_3)
            btnSolOpen_3.Layout__BelowControl(l5)
            Dim btnSolClose_3 As New SIL3.ApplicationSupport.ButtonHelper(100, "Close", AddressOf Me.btnSolClose_3)
            btnSolClose_3.Layout__RightOfControl(btnSolOpen_3)



        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        Private Sub btnSolOpen_0(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 0
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                                 iIndex, 1, 0)
        End Sub

        Private Sub btnSolClose_0(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 0
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                               iIndex, 0, 0)
        End Sub

        Private Sub btnSolOpen_1(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 1
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                                 iIndex, 1, 0)
        End Sub

        Private Sub btnSolClose_1(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 1
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                               iIndex, 0, 0)
        End Sub
        Private Sub btnSolOpen_2(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 2
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                                 iIndex, 1, 0)
        End Sub

        Private Sub btnSolClose_2(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 2
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                               iIndex, 0, 0)
        End Sub
        Private Sub btnSolOpen_3(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 3
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                                 iIndex, 1, 0)
        End Sub

        Private Sub btnSolClose_3(sender As Object, e As EventArgs)
            Dim iIndex As Integer = 3
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                               iIndex, 0, 0)
        End Sub




#End Region '#Region "BUTTON"

    End Class


End Namespace
