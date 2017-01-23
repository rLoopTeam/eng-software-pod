Namespace SIL3.rLoop.rPodControl

    ''' <summary>
    ''' Toolbox for rPod Controller Top level
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Toolbox

#Region "CONSTANTS"

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        ''' <summary>
        ''' The explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper

        ''' <summary>
        ''' The settings panel
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pnlSettings As SIL3.rLoop.rPodControl.Panels.Settings.Top

        ''' <summary>
        ''' The Flight Control Interface
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pnlFlightControl As SIL3.rLoop.rPodControl.Panels.FlightControl.Top

        ''' <summary>
        ''' Xilinx simulation module
        ''' </summary>
        Private m_pnlXilinxSim As SIL3.rLoop.rPodControl.Panels.XilinxSim.Top

        ''' <summary>
        ''' The ethernet interface
        ''' </summary>
        Private m_pEth As SIL3.rLoop.rPodControl.Ethernet.EthInterface

        ''' <summary>
        ''' The lower status strip
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pSS As SIL3.ApplicationSupport.StatusStripHelper


#End Region '#Region "MEMBERS"

#Region "NEW"


        ''' <summary>
        ''' create a new instance
        ''' </summary>
        ''' <param name="pForm"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pForm As Form)

            'create the form
            Me.Layout(pForm)

            Me.m_pEth = New SIL3.rLoop.rPodControl.Ethernet.EthInterface()

            'add our ports
            'http://confluence.rloop.org/display/SD/Communications

            If MsgBox("Do you want to run this in loopback?" & Environment.NewLine & "Else it will run on .0.x hardware", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
                Me.m_pEth.Port__Add("127.0.0.1", 9100, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU)
                Me.m_pEth.Port__Add("127.0.0.1", 3000, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU_SPACEX_DIAG)
                Me.m_pEth.Port__Add("127.0.0.1", 9170, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM)
            Else
                Me.m_pEth.Port__Add("192.168.0.100", 9100, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU)
                Me.m_pEth.Port__Add("192.168.0.100", 3000, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU_SPACEX_DIAG)
                Me.m_pEth.Port__Add("192.168.0.170", 9170, Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM)

            End If


            'rx handler
            AddHandler Me.m_pEth.UserEvent__UDPSafe__RxPacketB, AddressOf Me.InternalEvent__UDPSafe__RxPacketB
            AddHandler Me.m_pEth.UserEvent__RxPacketA, AddressOf Me.InternalEvent__RxPacketA

        End Sub

        ''' <summary>
        ''' Close the application
        ''' </summary>
        ''' <remarks></remarks>
        Public Sub Destroy()

            'Kill the eth interface
            Me.m_pEth.Destroy()

        End Sub

#End Region '#Region "NEW"

#Region "LAYOUT"
        ''' <summary>
        ''' Create the layout.
        ''' </summary>
        ''' <remarks></remarks>
        Private Sub Layout(ByRef pForm As Form)


            'setup the form
            pForm.Text = "rPod Control Toolbox (Build" & My.Application.Info.Version.ToString & ")"
            'pF.BackColor = Color.White
            pForm.WindowState = FormWindowState.Maximized

            'setup the explorer bar
            Me.m_pExplorer = New SIL3.ApplicationSupport.ExplorerBarHelper(Nothing)

            Me.m_pExplorer.Bar__ImageList_Add("bullet_square_green.png")
            Me.m_pExplorer.Bar__ImageList_Add("bullet_square_yellow.png")
            Me.m_pExplorer.Bar__ImageList_Add("bullet_square_red.png")

            Me.m_pnlSettings = New SIL3.rLoop.rPodControl.Panels.Settings.Top(pForm, Me.m_pExplorer)



            Me.m_pnlFlightControl = New SIL3.rLoop.rPodControl.Panels.FlightControl.Top(pForm, Me.m_pExplorer, Me.m_pnlSettings.Get__DataLogDir)
            AddHandler Me.m_pnlFlightControl.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlightControl.UserEvent__SafeUDP__Tx_X3_Array, AddressOf Me.InternalEvent__SafeUDP__Tx_X3_Array


            Me.m_pnlXilinxSim = New SIL3.rLoop.rPodControl.Panels.XilinxSim.Top(pForm, Me.m_pExplorer)
            AddHandler Me.m_pnlXilinxSim.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

            'add to our form (do this at the end to prevent window overlapping)
            Me.m_pExplorer.Set__Form(pForm)
            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

            'Create the status strip helper.
            Me.m_pSS = New SIL3.ApplicationSupport.StatusStripHelper(pForm)

        End Sub

#End Region '#Region "LAYOUT"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlSettings.Panel__HideShow(sText)
            Me.m_pnlFlightControl.Panel__HideShow(sText)
            Me.m_pnlXilinxSim.Panel__HideShow(sText)
        End Sub
#End Region '#Region "EXPLORER BAR"

#Region "ETHERNET TX"

        ''' <summary>
        ''' Some lower module wants to transmit to to the eth
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        Public Sub InternalEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            Me.m_pEth.User__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub

        ''' <summary>
        ''' 3x Blocks and a array
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="pu8Array"></param>
        ''' <param name="iArrayLength"></param>
        Private Sub InternalEvent__SafeUDP__Tx_X3_Array(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, pu8Array() As Byte, iArrayLength As Integer)
            Me.m_pEth.User__SafeUDP__Tx_X3_Array(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, pu8Array, iArrayLength)

        End Sub

#End Region '#Region "ETHERNET TX"


#Region "ETHERNET RX"
        ''' <summary>
        ''' New Packet Rx'd
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16PacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        ''' <param name="bCRC_OK"></param>
        ''' <param name="u32Sequence"></param>
        Private Sub InternalEvent__UDPSafe__RxPacketB(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16PacketType As UInt16, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)

            Select Case eEndpoint
                Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM
                    Me.m_pnlXilinxSim.InternalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC, bCRC_OK, u32Sequence)
                Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU
                    Me.m_pnlFlightControl.InternalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC, bCRC_OK, u32Sequence)
            End Select

        End Sub

        ''' <summary>
        ''' Raw packet
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u8Array"></param>
        ''' <param name="iLength"></param>
        Private Sub InternalEvent__RxPacketA(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u8Array() As Byte, iLength As Integer)
            Select Case eEndpoint
                Case Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU_SPACEX_DIAG
                    Me.m_pnlFlightControl.InternalEvent__RxPacketA(u8Array, iLength)
            End Select
        End Sub

#End Region '#Region "ETHERNET RX"

    End Class

End Namespace