Namespace SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase

    ''' <summary>
    ''' Monitor the flight controllers internal DB
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Monitor
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"

#End Region '#Region "CONSTANTS"

#Region "ENUMS"
        Private Enum _eUploadStates
            UPLOAD_STATE__IDLE
            UPLOAD_STATE__SEND_CHUNK
            UPLOAD_STATE__WAIT_CHUNK_ACK
            UPLOAD_STATE__CHUNK_ACKED
        End Enum
#End Region '#Region "ENUMS"

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

        ''' <summary>
        ''' The state for uploding
        ''' </summary>
        Private m_eUploadState As _eUploadStates

        ''' <summary>
        ''' Run our thread
        ''' </summary>
        Private m_bRunThread As Boolean

        ''' <summary>
        ''' the upload thread
        ''' </summary>
        Private m_pThread As System.Threading.Thread

        Private m_iChunkCount As Integer = 0

        Private m_sFileName As String

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

        Public Event UserEvent__SafeUDP__Tx_X3_Array(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, pu8Array() As Byte, iArrayLength As Integer)


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

                    If Me.m_eUploadState = _eUploadStates.UPLOAD_STATE__WAIT_CHUNK_ACK Then
                        Me.m_eUploadState = _eUploadStates.UPLOAD_STATE__CHUNK_ACKED
                    End If

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

            If MsgBox("Are you sure you want to upload?", MsgBoxStyle.YesNo) = MsgBoxResult.No Then
                Exit Sub
            End If

            Me.m_bRunThread = True
            Me.m_sFileName = Me.m_cboTrackToUpload.SelectedItem.ToString
            Me.m_pThread = New System.Threading.Thread(AddressOf Me.Thread_Run)
            Me.m_pThread.Start()

        End Sub



#End Region '#Region "BUTTON HELPERS"

#Region "THREADING"
        ''' <summary>
        ''' The threadings
        ''' </summary>
        Private Sub Thread_Run()

            'load the file

            Dim pF As New SIL3.FileSupport.BinaryFileReader(Me.m_sFileName, IO.FileMode.Open)
            Dim u8Array() As Byte = pF.Get_AllBytes
            Dim iFileSize As Integer = pF.GetFileSize
            Dim u8Tx((56 * 16) - 1) As Byte
            Dim iTxPos As Integer = 0

            Do While Me.m_bRunThread = True

                Select Case Me.m_eUploadState
                    Case _eUploadStates.UPLOAD_STATE__IDLE
                        Me.m_iChunkCount = 0

                        'just move on
                        Me.m_eUploadState = _eUploadStates.UPLOAD_STATE__SEND_CHUNK

                    Case _eUploadStates.UPLOAD_STATE__SEND_CHUNK

                        'format the chunk
                        For iCounter As Integer = 0 To (56 * 16) - 1
                            u8Tx(iCounter) = u8Array(iTxPos)
                            iTxPos += 1
                        Next

                        'send it
                        RaiseEvent UserEvent__SafeUDP__Tx_X3_Array(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_FLT__TX_TRACK_DB_CHUNK,
                                                0, Me.m_iChunkCount, (56 * 16), u8Tx, (56 * 16))

                        Me.m_eUploadState = _eUploadStates.UPLOAD_STATE__WAIT_CHUNK_ACK


                    Case _eUploadStates.UPLOAD_STATE__WAIT_CHUNK_ACK

                        'will be acked via reception

                    Case _eUploadStates.UPLOAD_STATE__CHUNK_ACKED

                        'the chunked got acked via return.


                End Select 'Select Case Me.m_eUploadState

                'wait for a bit
                System.Threading.Thread.Sleep(5)

            Loop ' Do While Me.m_bRunThread = True

        End Sub

#End Region '#Region "THREADING"

    End Class


End Namespace
