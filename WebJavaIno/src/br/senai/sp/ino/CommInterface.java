package br.senai.sp.ino;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import com.fazecast.jSerialComm.SerialPort;



public class CommInterface {

	public void enviar(String status, PrintWriter saida, SerialPort porta) throws Exception {
		saida.print(status);
		saida.flush();
	}

	public void receber(BufferedReader entrada, PrintWriter saida , SerialPort porta) {

		System.out.println("receber");
		try {
			String linha = "";
			DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

			entrada.toString();
			while ((linha = entrada.readLine()) != null) {

				System.out.println(" " + linha + " || " + dtf.format(LocalDateTime.now()));
			}

			System.out.println("Voltei do arduino");
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

	}

	public void receberTemp(BufferedReader entrada, PrintWriter saida, SerialPort porta) {

		try {
			String linha = "";
			DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

			entrada.toString();
			while ((linha = entrada.readLine()) != null) {

				System.out.println(" " + linha + " || " + dtf.format(LocalDateTime.now()));
			}

			System.out.println("Voltei do arduino");
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}

	}
}
