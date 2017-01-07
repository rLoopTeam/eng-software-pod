Namespace SIL3.rLoop.rPodControl.Panels.XilinxSim

    ''' <summary>
    ''' Top level xilinx sim
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Top

#Region "MEMBERS"
        ''' <summary>
        ''' Our application explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper

        ''' <summary>
        ''' The index of our category in the explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_iBarIndex As Integer

        ''' <summary>
        ''' Accelerometer control panel
        ''' </summary>
        Private m_pnlXilinx__ContrastNav As SIL3.rLoop.rPodControl.Panels.XilinxSim.ContrastNav


#End Region '#Region "MEMBERS"

#Region "EVENTS"

        ''' <summary>
        ''' Raise an event to transmit a new packet
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

#End Region '#Region "EVENTS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="pf"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pf As Windows.Forms.Form, ByRef pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper)

            'setup our explorer bar
            Me.m_pExplorer = pExplorer

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Xilinx Simulation")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Contrast Nav")


            'add the panels before the bar so as we have docking working well.
            Me.m_pnlXilinx__ContrastNav = New SIL3.rLoop.rPodControl.Panels.XilinxSim.ContrastNav("Contrast Nav")
            pf.Controls.Add(Me.m_pnlXilinx__ContrastNav)


            'setup eth
            AddHandler Me.m_pnlXilinx__ContrastNav.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

        End Sub

#End Region '#Region "NEW"

#Region "PANEL HELPERS"
        ''' <summary>
        ''' How or hide this panel if our text matches
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Public Sub Panel__HideShow(sText As String)
            Me.m_pnlXilinx__ContrastNav.Panel__HideShow(sText)
        End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlXilinx__ContrastNav.Panel__HideShow(sText)
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
        Private Sub InternalEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub

#End Region '#Region "ETHERNET TX"

#Region "ETHERNET RX"

        ''' <summary>
        ''' New packet in from top layer
        ''' </summary>
        ''' <param name="u16PacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        ''' <param name="bCRC_OK"></param>
        ''' <param name="u32Sequence"></param>
        Public Sub InternalEvent__UDPSafe__RxPacketB(u16PacketType As UInt16, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)
            Me.m_pnlXilinx__ContrastNav.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
        End Sub

#End Region '#Region "ETHERNET RX"


    End Class

End Namespace
