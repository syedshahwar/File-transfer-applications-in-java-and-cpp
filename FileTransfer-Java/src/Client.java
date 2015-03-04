
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.Socket;

public class Client {
public static void main(String[] args) throws IOException {

FileInputStream instream = null;
BufferedInputStream bufferedInStream = null;
BufferedOutputStream bufferedOutStream = null;
Socket s = null;
int counter;

try{
    try {
           s = new Socket("127.0.0.1", 55555);
        } catch (IOException ex) {
            System.out.println("Error: Unable to create Socket ");
        }

            File file = new File("E:/sample.txt");
            long fileLength = file.length();
            System.out.println("File Size: "+fileLength);
            if ( Integer.MAX_VALUE < fileLength ) 
            {
                    System.out.println("Error: Exceeded the size of transfer");
            }


            byte[] bytes = new byte[(int) fileLength];
            try{
                 instream = new FileInputStream(file);
                }catch (IOException ex){
                    System.out.println("Error: Unable to open fileInputStream");
                }
            bufferedInStream = new BufferedInputStream(instream);
            bufferedOutStream = new BufferedOutputStream(s.getOutputStream());

while ((counter = bufferedInStream.read(bytes)) > 0) {
    bufferedOutStream.write(bytes, 0, counter);
}
}

finally{
        bufferedOutStream.flush();
        bufferedOutStream.close();
        instream.close();
        bufferedInStream.close();
        s.close();
}

}
}