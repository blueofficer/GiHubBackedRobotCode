import java.io.IOException;
import java.net.ServerSocket;

public class StartConnectionRobot extends Thread{
    ServerSocket robotConnection;

    public StartConnectionRobot() {
        try {
            robotConnection = new ServerSocket(2222);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) {
            try {
                PassThrough.setUpRobotConnection(robotConnection.accept());
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
}
