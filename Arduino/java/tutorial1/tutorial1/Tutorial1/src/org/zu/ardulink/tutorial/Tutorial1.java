package org.zu.ardulink.tutorial;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;

import org.zu.ardulink.Link;
import org.zu.ardulink.gui.ConnectionPanel;
import org.zu.ardulink.gui.PWMController;

import com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel;

public class Tutorial1 extends JFrame {

	private static final long serialVersionUID = -5884548646729927244L;

	// 2. Define the contentPane and an ardulink connection panel
	private JPanel contentPane;
	private ConnectionPanel connectionPanel;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					// 1. Change Look and Feel
					UIManager.setLookAndFeel(NimbusLookAndFeel.class.getCanonicalName());
					
					Tutorial1 frame = new Tutorial1();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Tutorial1() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 475, 375);
		// 3. Setup the contentPane
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));

		// 4. Insert the defined connection Panel
		connectionPanel = new ConnectionPanel();
		connectionPanel.setLayout(null);
		contentPane.add(connectionPanel, BorderLayout.WEST);

		// 5. Insert a connection button
		JButton btnConnect = new JButton("Connect");
		// 7. Add an action listener when the connection button is pressed
		btnConnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 8. Take connection parameters
				String connectionPort = connectionPanel.getConnectionPort();
				int baudRate = Integer.parseInt(connectionPanel.getBaudRate());

				// 9. Let's go. Link it to Arduino.
				boolean connected = Link.getDefaultInstance().connect(connectionPort, baudRate);

				// 10. Just an information message
				if(connected) {
					JOptionPane.showMessageDialog(connectionPanel, "Arduino connected", "Connection Status", JOptionPane.INFORMATION_MESSAGE);
				} else {
					JOptionPane.showMessageDialog(connectionPanel, "Arduino NOT connected", "Connection Status", JOptionPane.ERROR_MESSAGE);
				}
				
			}
		});
		contentPane.add(btnConnect, BorderLayout.SOUTH);

		// 6. Insert an ardulink power with modulation pin controller
		PWMController powerPinPanel = new PWMController();
		powerPinPanel.setPin(11);
		contentPane.add(powerPinPanel, BorderLayout.EAST);
		
		
		
	}

}
