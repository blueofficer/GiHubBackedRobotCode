import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.JFrame;

/**
 * IsKeyPressed
 */
public class KeyBoardcontroller {

    static BufferedReader serverReader = null;
    static PrintWriter serverWriter = null;

    static int servoAngle = 90;

    public static void main(String[] args) throws IOException {

        Socket clientConnection = new Socket("192.168.50.1", 4444);

        serverReader = new BufferedReader(new InputStreamReader(clientConnection.getInputStream()));
        serverWriter = new PrintWriter(clientConnection.getOutputStream(), true);

        System.out.println(serverReader.readLine());
        // s
        JFrame frame = new JFrame("listiner");

        frame.setSize(400, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        frame.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                // TODO Auto-generated method stub

                int keycode = e.getKeyCode();

                switch (keycode) {
                    case KeyEvent.VK_W:
                        serverWriter.println("DFFFF");
                        break;
                    case KeyEvent.VK_SPACE:
                        serverWriter.println("DSSSS");
                        break;
                    case KeyEvent.VK_S:
                        serverWriter.println("DBBBB");
                        break;
                    case KeyEvent.VK_D:
                        serverWriter.println("DFFBB");
                        break;
                    case KeyEvent.VK_A:
                        serverWriter.println("DBBFF");
                        break;
                    case KeyEvent.VK_DOWN:
                        serverWriter.println("DBBBB");
                        break;
                    case KeyEvent.VK_RIGHT:
                        serverWriter.println("DFFBB");
                        break;
                    case KeyEvent.VK_LEFT:
                        serverWriter.println("DBBFF");
                        break;
                    case KeyEvent.VK_UP:
                        serverWriter.println("DFFFF");
                        break;
                    case KeyEvent.VK_3:
                        serverWriter.println("DFFFF");
                        break;
                    case KeyEvent.VK_E:
                        if (servoAngle > 60) {
                            servoAngle -= 10;
                            serverWriter.println("S" + (char) servoAngle);
                        }
                        break;
                    case KeyEvent.VK_Q:
                        if (servoAngle < 120) {
                            servoAngle += 10;
                            serverWriter.println("S" + (char) servoAngle);
                        }
                        break;
                    case KeyEvent.VK_2:
                        servoAngle = 90;
                        serverWriter.println("S" + (char) servoAngle);
                        break;
                    case KeyEvent.VK_1:
                        serverWriter.println("1");
                        break;
                    case KeyEvent.VK_M:
                        serverWriter.println("M"); // TODO: add the ablyty to switch music tracs music
                        break;

                    default:
                        break;
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                int keycode = e.getKeyCode();

                switch (keycode) {
                    case KeyEvent.VK_W:
                        serverWriter.println("DSSSS");
                        break;
                    case KeyEvent.VK_SPACE:
                        serverWriter.println("DSSSS");
                        break;
                    case KeyEvent.VK_S:
                        serverWriter.println("DSSSS");
                        break;
                    case KeyEvent.VK_D:
                        serverWriter.println("DSSSS");
                        break;
                    case KeyEvent.VK_A:
                        serverWriter.println("DSSSS");
                        break;
                    default:
                        break;
                }
            }
        });

        frame.setVisible(true);
    }
}