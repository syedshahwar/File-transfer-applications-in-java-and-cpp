import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {


public static void main(String[] args) throws IOException {
    ServerSocket serverSocket = null;
    Socket s = null;
    InputStream inStream = null;
    FileOutputStream fileOutStream = null;
    BufferedOutputStream bufferedOutStream = null;
    int buffSize = 0;

    try{

            try {
                    serverSocket = new ServerSocket(55555);
                } catch (IOException ex) {
                    System.out.println("Error: Unable to Connect to Server ");
                }
            System.out.println("Server Starts");
            try {
                    s = serverSocket.accept();
                } catch (IOException ex) {
                    System.out.println("Error: Unable to connect to client ");
                }
            System.out.println("Client Connection accepted");
            try {
                    inStream = s.getInputStream();
                    buffSize = s.getReceiveBufferSize();
                   // System.out.println("Size of Buffer " + sizeBuffer);
                } catch (IOException ex) {
                        System.out.println("Error: unable to ger socket input stream ");
                }       

            try {
                    fileOutStream = new FileOutputStream("E:/out-java.txt");
                    bufferedOutStream = new BufferedOutputStream(fileOutStream);

                } catch (FileNotFoundException ex) {
                        System.out.println("File not found. ");
                }

            byte[] bytes = new byte[buffSize];

            int count;

            while ((count = inStream.read(bytes)) > 0) {
                    bufferedOutStream.write(bytes, 0, count);
            }

            System.out.println("\nFile has been uploaded on Server");
    }// end of first try

    finally
    {
    bufferedOutStream.flush();
    bufferedOutStream.close();
    inStream.close();
    s.close();
    serverSocket.close();
    }
}

}
