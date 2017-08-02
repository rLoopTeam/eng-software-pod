Namespace SIL3.rLoop.rPodControl.Panels.HETherm

    ''' <summary>
    ''' Top level HET Panel
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Top

#Region "MEMBERS"
        ''' <summary>
        ''' Our application explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pExplorer As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ExplorerBarHelper

        ''' <summary>
        ''' The index of our category in the explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_iBarIndex As Integer

        Private m_pnlHET__Manual As SIL3.rLoop.rPodControl.Panels.HETherm.Manual
        Private m_pnlHET__Temp As SIL3.rLoop.rPodControl.Panels.HETherm.TempSensors
        Private m_pnlHET__Auto As SIL3.rLoop.rPodControl.Panels.HETherm.AutoControl

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="pf"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pf As Windows.Forms.Form, ByRef pExplorer As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ExplorerBarHelper)

            'setup our explorer bar
            Me.m_pExplorer = pExplorer

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Hover Engine Thermal")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "HET - Auto Control")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "HET - Manual")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "HET - Temp Sensors")


            'add the panels before the bar so as we have docking working well.
            Me.m_pnlHET__Manual = New SIL3.rLoop.rPodControl.Panels.HETherm.Manual("HET - Manual")
            pf.Controls.Add(Me.m_pnlHET__Manual)
            Me.m_pnlHET__Temp = New SIL3.rLoop.rPodControl.Panels.HETherm.TempSensors("HET - Temp Sensors")
            pf.Controls.Add(Me.m_pnlHET__Temp)
            Me.m_pnlHET__Auto = New SIL3.rLoop.rPodControl.Panels.HETherm.AutoControl("HET - Auto Control")
            pf.Controls.Add(Me.m_pnlHET__Auto)


            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

            AddHandler Me.m_pnlHET__Manual.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlHET__Auto.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlHET__Temp.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

        End Sub

#End Region '#Region "NEW"

#Region "EVENTS"
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

#End Region '#Region "EVENTS"

#Region "PANEL HELPERS"
        ''' <summary>
        ''' How or hide this panel if our text matches
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Public Sub Panel__HideShow(sText As String)
            Me.m_pnlHET__Manual.Panel__HideShow(sText)
            Me.m_pnlHET__Auto.Panel__HideShow(sText)
            Me.m_pnlHET__Temp.Panel__HideShow(sText)

        End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlHET__Manual.Panel__HideShow(sText)
            Me.m_pnlHET__Auto.Panel__HideShow(sText)
            Me.m_pnlHET__Temp.Panel__HideShow(sText)
        End Sub
#End Region '#Region "EXPLORER BAR"

#Region "ETHERNET TX"

        ''' <summary>
        ''' Internally we want to transmit a UDP packet
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
        Public Sub InternalEvent__UDPSafe__RxPacketB(u16PacketType As UInt16, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)
            Me.m_pnlHET__Auto.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload)
            Me.m_pnlHET__Temp.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload)
        End Sub

        ''' <summary>
        ''' Rx a eth packet
        ''' </summary>
        ''' <param name="u8Array"></param>
        ''' <param name="iLength"></param>
        Public Sub InternalEvent__RxPacketA(u8Array() As Byte, iLength As Integer)
        End Sub


#End Region '#Region "ETHERNET RX"


    End Class

End Namespace
