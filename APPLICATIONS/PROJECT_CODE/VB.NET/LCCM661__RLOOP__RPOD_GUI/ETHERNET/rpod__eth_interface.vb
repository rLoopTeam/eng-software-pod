Namespace SIL3.rLoop.rPodControl.Ethernet

    ''' <summary>
    ''' Ethernet Interface
    ''' </summary>
    ''' <remarks></remarks>
    Public Class EthInterface

#Region "STRUCTURES"

        ''' <summary>
        ''' Just a type so as we know what port to head out
        ''' </summary>
        Public Structure _strUDP_Endpoint

            Dim pSafeUDP As SIL3.SafeUDP.StdUDPLayer

            Dim iPort As Integer

            Dim eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS

        End Structure

#End Region '#Region "STRUCTURES"

#Region "MEMBERS"
        ''' <summary>
        ''' List of endpoints
        ''' </summary>
        Private m_lUDP As List(Of _strUDP_Endpoint)

#End Region '#Region "MEMBERS"

#Region "NEW"

        ''' <summary>
        ''' Create a new ethernet interface
        ''' </summary>
        Public Sub New()

            'init our list
            Me.m_lUDP = New List(Of _strUDP_Endpoint)

        End Sub

        ''' <summary>
        ''' Called to kill all our lower systems
        ''' </summary>
        Public Sub Destroy()
            For Each pX As _strUDP_Endpoint In Me.m_lUDP
                pX.pSafeUDP.Destroy()
            Next
        End Sub

#End Region '#Region "NEW"

#Region "EVENTS"

        ''' <summary>
        ''' Called when a new packet arives from the SafeUDP
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16PacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        ''' <param name="bCRC_OK"></param>
        ''' <param name="u32Sequence"></param>
        Public Event UserEvent__UDPSafe__RxPacketB(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16PacketType As UInt16, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)

        Public Event UserEvent__RxPacketA(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u8Array() As Byte, iLength As Integer)

#End Region '#Region "EVENTS"

#Region "ADD PORTS"

        ''' <summary>
        ''' Add a new port to be monitored by the system
        ''' </summary>
        ''' <param name="sIP"></param>
        ''' <param name="iPort"></param>
        ''' <param name="eEndpoint"></param>
        Public Sub Port__Add(sIP As String, iPort As Integer, eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS)

            'new port
            Dim pY As _strUDP_Endpoint
            pY.pSafeUDP = New SIL3.SafeUDP.StdUDPLayer(sIP, iPort, "SafeUDP_" & iPort.ToString, True, True)
            pY.eEndpoint = eEndpoint
            pY.iPort = iPort

            AddHandler pY.pSafeUDP.UserEvent__UDPSafe__RxPacketA, AddressOf Me.InernalEvent__UDPSafe__RxPacketA
            AddHandler pY.pSafeUDP.UserEvent__NewPacketA, AddressOf Me.InternalEvent__RxPacketA
            'AddHandler pY.pSafeUDP.UserEvent__UDPSafe__RxPacket, Function(ePacketType, u16PayloadLength, u8Payload, u16CRC, bCRCOK, u32Seq) InernalEvent__UDPSafe__RxPacket(eEndpoint, ePacketType, u16PayloadLength, u8Payload, u16CRC, bCRCOK, u32Seq)

            'add to our list
            Me.m_lUDP.Add(pY)

        End Sub

#End Region

#Region "TRANSMIT"
        ''' <summary>
        ''' Transmit out the Eth
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        Public Sub User__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

            For Each pX As _strUDP_Endpoint In Me.m_lUDP
                If pX.eEndpoint = eEndpoint Then
                    pX.pSafeUDP.Tx__Safe_ControlPacket(u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
                End If
            Next

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
        Public Sub User__SafeUDP__Tx_X3_Array(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, pu8Array() As Byte, iArrayLength As Integer)

            For Each pX As _strUDP_Endpoint In Me.m_lUDP
                If pX.eEndpoint = eEndpoint Then
                    pX.pSafeUDP.Tx__Safe_ControlPacket_X3_Array(u16Type, u32Block0, u32Block1, u32Block2, pu8Array, iArrayLength)
                End If
            Next

        End Sub

#End Region

#Region "RX HANDLERS"

        ''' <summary>
        ''' New RAW packet
        ''' </summary>
        ''' <param name="iPort"></param>
        ''' <param name="u8Array"></param>
        ''' <param name="iLength"></param>
        Private Sub InternalEvent__RxPacketA(iPort As Integer, u8Array() As Byte, iLength As Integer)
            For Each pX As _strUDP_Endpoint In Me.m_lUDP
                If pX.iPort = iPort Then
                    RaiseEvent UserEvent__RxPacketA(pX.eEndpoint, u8Array, iLength)
                End If
            Next

        End Sub

        ''' <summary>
        '''  New packet has come in
        ''' </summary>
        ''' <param name="iPort"></param>
        ''' <param name="u16PacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        ''' <param name="bCRCOK"></param>
        ''' <param name="u32Seq"></param>
        Private Sub InernalEvent__UDPSafe__RxPacketA(iPort As Integer, u16PacketType As UInt16, ByVal u16PayloadLength As Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As Numerical.U16, ByVal bCRCOK As Boolean, ByVal u32Seq As UInt32)

            'work out who owns it and send it off.
            For Each pX As _strUDP_Endpoint In Me.m_lUDP
                If pX.iPort = iPort Then
                    RaiseEvent UserEvent__UDPSafe__RxPacketB(pX.eEndpoint, u16PacketType, u16PayloadLength, u8Payload, u16CRC, bCRCOK, u32Seq)
                End If
            Next

        End Sub

        Private Sub InternalEvent__ARP__Packet(ByVal u8SenderHW() As Numerical.U8, ByVal u8SenderIP() As Numerical.U8, ByVal u16LFW As Numerical.U16, ByVal u8FWMajor As Numerical.U8, ByVal u8FWMinor As Numerical.U8)
        End Sub

#End Region '#Region "RX HANDLERS"

#Region "TX HANDLERS"

        Private Sub InternalEvent__UDPSafe__TxArray(ByVal u16PacketType As SIL3.SafeUDP.PacketTypes.SAFE_UDP__PACKET_T, ByVal u16PayloadLength As UInt16, ByRef bData() As Byte)
        End Sub
#End Region


    End Class

End Namespace
