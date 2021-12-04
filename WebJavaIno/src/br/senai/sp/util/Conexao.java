package br.senai.sp.util;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import com.fazecast.jSerialComm.SerialPort;



public class Conexao {

	public static PrintWriter saida;
	public static SerialPort porta;
	public static MinhaConexao mc = new MinhaConexao();
	public static BufferedReader entrada;

	static class MinhaConexao {
		
		public MinhaConexao() {
			System.out.println("Minha Conexao Construtor");

			porta = SerialPort.getCommPorts()[0];
			porta.setComPortTimeouts(SerialPort.LISTENING_EVENT_DATA_AVAILABLE, 0, 0);
			porta.setBaudRate(9600);
			porta.openPort();

			entrada = new BufferedReader(new InputStreamReader(porta.getInputStream()));
			saida = new PrintWriter(porta.getOutputStream()); 
		}
	}

}