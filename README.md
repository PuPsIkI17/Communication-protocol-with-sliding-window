# Communication Protocol With Sliding Window

</br>&nbsp;&nbsp;&nbsp;The project implements a communication protocol with the sliding window used to transmit a file. The file will be sent by the transmitter (send.c) and sent to the receiver (rec.c). The implemented protocol effectively uses the data link: the data link must be kept full. The transmitter receives the following arguments: 
</br>&nbsp;&nbsp;&nbsp;• the filename of the file to be transmitted (XX files)
</br>&nbsp;&nbsp;&nbsp;• the transmission speed (Mbps) 
</br>&nbsp;&nbsp;&nbsp;• the propagation time (ms) The receiver will save t</br>&nbsp;&nbsp;&nbsp;he data received in the XXX file (name the file must be transmitted to the sender receiver).

</br>&nbsp;&nbsp;&nbsp;Features
</br>&nbsp;&nbsp;&nbsp;• The efficient transmission of the file when the data link does not lose or corrupt the frames. 
</br>&nbsp;&nbsp;&nbsp;• The correct and efficient transmission of the file when the data link does not corrupt the data, but it may lose frames. Maximum 10% of the staff are lost.
</br>&nbsp;&nbsp;&nbsp;• The correct and efficient transmission of the file when the data link can lose and corrupt the frames. Maximum 10% of the staff are lost. Maximum 10% of the cadres are corrupted. 
</br>&nbsp;&nbsp;&nbsp;• The correct and efficient transmission of the file when the data link reorders the frames.

</br>&nbsp;&nbsp;&nbsp;Parameters
</br>&nbsp;&nbsp;&nbsp;• The propagation speed and time are constant (these parameters are set and will not change during program execution). 
</br>&nbsp;&nbsp;&nbsp;• The transmission speed has values between 5Mbps and 20 Mbps. 
</br>&nbsp;&nbsp;&nbsp;• The propagation time has values between 10ms and 1000ms.
</br>&nbsp;&nbsp;&nbsp;• The data link may lose up to 10% of the sent frames. The confirmations (sent by the receiver) are not lost, they are not corrupted and they are transmitted instantly. 
</br>&nbsp;&nbsp;&nbsp;• The data link can reorder the packets.
</br>&nbsp;&nbsp;&nbsp;• The data link can corrupt up to 10% of the sent frames.
</br>&nbsp;&nbsp;&nbsp;• A corrupted account framework holds a single invalid byte in the payload field of the msg structure in lib.h. 
</br>&nbsp;&nbsp;&nbsp;• The parameters for the data link are set from the run experiment.sh script. Valid values, as specified above, are:
</br>&nbsp;&nbsp;&nbsp;- SPEED = 5 ... 20 
</br>&nbsp;&nbsp;&nbsp;- DELAY = 10 ... 1000 
</br>&nbsp;&nbsp;&nbsp;- LOSS = 0 ... 10 
</br>&nbsp;&nbsp;&nbsp;- CORRUPT = 0 ... 10 
</br>&nbsp;&nbsp;&nbsp;- REORDER = 0 ... 10
