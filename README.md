# minitalk
42 Curriculum (Level 3) - Simulate the behavior of a client (which has to send a string) and a server (which receives and displays the string)

## Use
`git clone` repository  
`make` within the minitalk directory to compile the 2 binaries  
`./server` to start server: this will print on the output its process id (CTRL+C to stop it)
`./client server_pid 'The string that you would like to send to the server'` to send the string to the other process (this command should be given in a different terminal)  
\*This project also supports UNICODE characters
