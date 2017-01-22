Namespace SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase

    ''' <summary>
    ''' Monitor the flight controllers internal DB
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Monitor
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String


        ''' <summary>
        ''' The database directory
        ''' </summary>
        Private m_sDBDir As String

        ''' <summary>
        ''' The track that we want to send to flight controller
        ''' </summary>
        Private m_cboTrackToUpload As SIL3.ApplicationSupport.ComboBoxHelper

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String, sLog As String)
            MyBase.New(sPanelText)

            Me.m_sLogDir = sLog
            Me.m_sLogDir = Me.m_sLogDir & "TRACK_DB\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            Me.m_sDBDir = "D:\LOCKIE\DESIGN\RLOOP\FIRMWARE\PROJECT_CODE\LCCM655__RLOOP__FCU_CORE\FLIGHT_CONTROLLER\TRACK_DATABASE\DATABASES\"


        End Sub
#End Region '#Region "New"

#Region "EVENTS"

        ''' <summary>
        ''' Raised wehen we want to transmit a control packet
        ''' </summary>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        ''' <remarks></remarks>

        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)


        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'check for our sim packet type
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_FLT__ACK_TRACK_DB_CHUNK Then


                End If
            End If

        End Sub


#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Select Track to Upload", MyBase.m_pInnerPanel)
            Me.m_cboTrackToUpload = New SIL3.ApplicationSupport.ComboBoxHelper(800, l0)

            'see if we have any bins
            Dim lBins As List(Of String) = SIL3.FileSupport.FileHelpers.Folder__GetFileList(Me.m_sDBDir)
            Dim lTotal As New List(Of String)
            For Each sTemp As String In lBins
                If sTemp.EndsWith(".bin") = True Then
                    lTotal.Add(sTemp)
                End If
            Next

            Me.m_cboTrackToUpload.Threadsafe__AddItem(lTotal)

            Dim btnUpload As New SIL3.ApplicationSupport.ButtonHelper(100, "Upload", AddressOf btnUpload__Click)
            btnUpload.Layout__RightOfControl(m_cboTrackToUpload)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Upload a file to the FCU
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnUpload__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 1, 0, 0, 0)
        End Sub



#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
