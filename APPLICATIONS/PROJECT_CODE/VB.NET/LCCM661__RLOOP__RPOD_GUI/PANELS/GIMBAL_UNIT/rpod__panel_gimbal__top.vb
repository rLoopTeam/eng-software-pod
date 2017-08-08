Namespace SIL3.rLoop.rPodControl.Panels.Gimbal

    ''' <summary>
    ''' Top level Gimbal Panel
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

        Private m_pnlGCU__Manual As SIL3.rLoop.rPodControl.Panels.Gimbal.Manual

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

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Gimbal Comtrol Unit")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "GCU - Manual")


            'add the panels before the bar so as we have docking working well.
            Me.m_pnlGCU__Manual = New SIL3.rLoop.rPodControl.Panels.Gimbal.Manual("GCU - Manual")
            pf.Controls.Add(Me.m_pnlGCU__Manual)


            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

            AddHandler Me.m_pnlGCU__Manual.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4

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
            Me.m_pnlGCU__Manual.Panel__HideShow(sText)

        End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlGCU__Manual.Panel__HideShow(sText)

        End Sub
#End Region '#Region "EXPLORER BAR"

#Region "ETHERNET"
        Public Sub InternalEvent__UDPSafe__RxPacketB(u16PacketType As UInt16, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)
        End Sub


        Private Sub InternalEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub

#End Region '#Region "ETHERNET"

    End Class

End Namespace
