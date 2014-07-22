/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.zu.ardulink.tutorial;


import java.util.Calendar;
import java.util.TimeZone;
import javax.swing.JOptionPane;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

/**
 *
 * @author MIR
 */
public class SerialFinal1 extends javax.swing.JPanel {

    static SerialPort serialPort = new SerialPort("COM3");
    static  long lastUpdateTime=0;
    static Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("UTC")); 
 
    /**
     * Creates new form SerialFinal1
     */
    public SerialFinal1() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        connectBtn = new javax.swing.JButton();
        disconnectBtn = new javax.swing.JButton();
        inputTb = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        logTb = new javax.swing.JTextArea();

        setPreferredSize(new java.awt.Dimension(564, 472));

        connectBtn.setText("Connect");
        connectBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                connectBtnActionPerformed(evt);
            }
        });

        disconnectBtn.setText("Disconnect");
        disconnectBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                disconnectBtnActionPerformed(evt);
            }
        });

        inputTb.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                inputTbActionPerformed(evt);
            }
        });

        logTb.setColumns(20);
        logTb.setRows(5);
        jScrollPane1.setViewportView(logTb);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(connectBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(disconnectBtn)
                        .addGap(0, 347, Short.MAX_VALUE))
                    .addComponent(inputTb, javax.swing.GroupLayout.Alignment.TRAILING))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(connectBtn)
                    .addComponent(disconnectBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 49, Short.MAX_VALUE)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 214, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(inputTb, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void connectBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_connectBtnActionPerformed
        try {
            boolean connected = serialPort.openPort();//Open serial port
            serialPort.setParams(9600, 8, 1, 0);//Set params
            int mask = SerialPort.MASK_RXCHAR + SerialPort.MASK_CTS + SerialPort.MASK_DSR;//Prepare mask
            serialPort.setEventsMask(mask);//Set mask
            serialPort.addEventListener(new SerialPortReader());//Add SerialPortEventListener

            if (connected) {
                JOptionPane.showMessageDialog(this, "Connection Succeesful", "", JOptionPane.PLAIN_MESSAGE);
            }

        } catch (SerialPortException ex) {
            System.out.println(ex);
        }
    }//GEN-LAST:event_connectBtnActionPerformed

    private void disconnectBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_disconnectBtnActionPerformed
        // TODO add your handling code here:
        boolean close = false;
        try {
            close = serialPort.closePort();
        } catch (SerialPortException ex) {

        }
        if (close) {
            JOptionPane.showMessageDialog(this, "Connection Close", "", JOptionPane.PLAIN_MESSAGE);
        }
    }//GEN-LAST:event_disconnectBtnActionPerformed

//    public static void main(String args[]) {
//        java.awt.EventQueue.invokeLater(new Runnable() {
//            public void run() {
//                new SerialFinal1().setVisible(true);
//            }
//        });
//    }
    private void inputTbActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_inputTbActionPerformed
        // TODO add your handling code here:
        boolean done = false;
        try {
            done = serialPort.writeString(inputTb.getText());
        } catch (Exception ex) {

        }
        if (done) {
            logTb.append(inputTb.getText() + "\n");
        }
        inputTb.setText("");
    }//GEN-LAST:event_inputTbActionPerformed

    static class SerialPortReader implements SerialPortEventListener {

        public void serialEvent(SerialPortEvent event) {
            
            if (event.isRXCHAR()) {//If data is available

                try {

                    System.out.println(serialPort.readString());
                    logTb.append("\n"+(int)System.currentTimeMillis()/1000);
                    return;

                        
                } catch (SerialPortException ex) {
                    System.out.println(ex);
                }
            } else if (event.isCTS()) {//If CTS line has changed state
                if (event.getEventValue() == 1) {//If line is ON
                    System.out.println("CTS - ON");
                } else {
                    System.out.println("CTS - OFF");
                }
            } else if (event.isDSR()) {///If DSR line has changed state
                if (event.getEventValue() == 1) {//If line is ON
                    System.out.println("DSR - ON");
                } else {
                    System.out.println("DSR - OFF");
                }
            }
        }
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton connectBtn;
    private javax.swing.JButton disconnectBtn;
    private javax.swing.JTextField inputTb;
    private javax.swing.JScrollPane jScrollPane1;
    public static javax.swing.JTextArea logTb;
    // End of variables declaration//GEN-END:variables
}
