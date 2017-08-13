Namespace SIL3.rLoop.rPodControl.Panels.BMS

    ''' <summary>
    ''' Top level BMS Channel A panel
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

        Private m_pnlBMS_Cells As SIL3.rLoop.rPodControl.Panels.BMS.Cells
        Private m_pnlBMS_Charger As SIL3.rLoop.rPodControl.Panels.BMS.Charger

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="pf"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pf As Windows.Forms.Form, ByRef pExplorer As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ExplorerBarHelper, sLogDir As String, iBMS_Index As Integer)

            'setup our explorer bar
            Me.m_pExplorer = pExplorer

            If iBMS_Index = 0 Then
                Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Battery - A")
                Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "BMS A - Cells")
                Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "BMS A - Charge Control")

                'add the panels before the bar so as we have docking working well.
                Me.m_pnlBMS_Cells = New SIL3.rLoop.rPodControl.Panels.BMS.Cells("BMS A - Cells", iBMS_Index)
                pf.Controls.Add(Me.m_pnlBMS_Cells)
                Me.m_pnlBMS_Charger = New SIL3.rLoop.rPodControl.Panels.BMS.Charger("BMS A - Charge Control", iBMS_Index)
                pf.Controls.Add(Me.m_pnlBMS_Charger)

            Else
                Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Battery - B")
                Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "BMS B - Cells")
                Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "BMS B - Charge Control")

                'add the panels before the bar so as we have docking working well.
                Me.m_pnlBMS_Cells = New SIL3.rLoop.rPodControl.Panels.BMS.Cells("BMS B - Cells", iBMS_Index)
                pf.Controls.Add(Me.m_pnlBMS_Cells)
                Me.m_pnlBMS_Charger = New SIL3.rLoop.rPodControl.Panels.BMS.Charger("BMS B - Charge Control", iBMS_Index)
                pf.Controls.Add(Me.m_pnlBMS_Charger)
            End If

            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

            AddHandler Me.m_pnlBMS_Cells.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlBMS_Charger.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

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
            Me.m_pnlBMS_Cells.Panel__HideShow(sText)
            Me.m_pnlBMS_Charger.Panel__HideShow(sText)
        End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlBMS_Charger.Panel__HideShow(sText)
            Me.m_pnlBMS_Cells.Panel__HideShow(sText)
        End Sub
#End Region '#Region "EXPLORER BAR"

#Region "ETHERNET"


        Private Sub InternalEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub

#End Region '#Region "ETHERNET"

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
            Me.m_pnlBMS_Cells.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload)
            Me.m_pnlBMS_Charger.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload)
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
