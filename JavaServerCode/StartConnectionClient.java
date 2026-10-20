import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class StartConnectionClient extends Thread{
    ServerSocket clientConnection;

    public StartConnectionClient() {
        try {
            clientConnection = new ServerSocket(4444);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) {
            try {
                PassThrough.setUpClientConnection(clientConnection.accept());
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
}
