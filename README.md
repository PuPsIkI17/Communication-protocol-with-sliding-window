# Communication Protocol With Sliding Window

The project implements a communication protocol with the sliding window used to transmit a file. The file will be sent by the transmitter (send.c) and sent to the receiver (rec.c). The implemented protocol effectively uses the data link: the data link must be kept full. The transmitter receives the following arguments: 
• the filename of the file to be transmitted (XX files)
• the transmission speed (Mbps) 
• the propagation time (ms) The receiver will save the data received in the XXX file (name the file must be transmitted to the sender receiver).

Features
• The efficient transmission of the file when the data link does not lose or corrupt the frames. 
• The correct and efficient transmission of the file when the data link does not corrupt the data, but it may lose frames. Maximum 10% of the staff are lost.
• The correct and efficient transmission of the file when the data link can lose and corrupt the frames. Maximum 10% of the staff are lost. Maximum 10% of the cadres are corrupted. 
• The correct and efficient transmission of the file when the data link reorders the frames.

Parameters
• The propagation speed and time are constant (these parameters are set and will not change during program execution). 
• The transmission speed has values between 5Mbps and 20 Mbps. 
• The propagation time has values between 10ms and 1000ms.
• The data link may lose up to 10% of the sent frames. The confirmations (sent by the receiver) are not lost, they are not corrupted and they are transmitted instantly. 
• The data link can reorder the packets.
• The data link can corrupt up to 10% of the sent frames.
• A corrupted account framework holds a single invalid byte in the payload field of the msg structure in lib.h. 
• The parameters for the data link are set from the run experiment.sh script. Valid values, as specified above, are:
- SPEED = 5 ... 20 - DELAY = 10 ... 1000 - LOSS = 0 ... 10 - CORRUPT = 0 ... 10 - REORDER = 0 ... 10
