import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class PassThrough {

    // Client Stuff
    /**
     * this is for reading the data from the java client and to send to the robot
     */
    private static BufferedReader clientReader = null;
    /** This is for sending to the robot */
    private static PrintWriter robotPrinter = null;

    // Robot Stuff
    /** this is for reading data from the robot and to send to the java client */
    private static BufferedReader robotReader = null;
    /** This is for sending to the java client */
    private static PrintWriter clientPrinter = null;


    public static void setUpClientConnection(Socket connection) throws IOException {
        clientReader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        clientPrinter = new PrintWriter(connection.getOutputStream(),true);
        System.out.println("client has been set up");
    }

    public static void setUpRobotConnection(Socket connection) throws IOException {
        robotReader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        robotPrinter = new PrintWriter(connection.getOutputStream(),true);
        System.out.println("Robot Has Benn Set Up");
    }

    public static void sendMessageToClient(String message) {
        clientPrinter.println(message);
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        new StartConnectionClient().start();
        new StartConnectionRobot().start();

        String clientMesage = "";

        //TODO: set up bi direction communication
        while (true) {
            if (clientReader != null && robotReader != null) {
                clientMesage = clientReader.readLine();
                System.out.println("Got this: " + clientMesage);
                robotPrinter.println(clientMesage);
            }else{
                System.out.println("Waiting for a connection");
                Thread.sleep(2000);
            }
        }
    }
}
