package br.senai.sp.serv;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.google.gson.Gson;

import br.senai.sp.ino.CommInterface;
import br.senai.sp.model.EnsaioConfig;
import br.senai.sp.model.Posicao;
import br.senai.sp.util.Conexao;

@WebServlet("/WebJava")
public class WebJava extends HttpServlet {

	private static float posXatual = 0;
	private static float posYatual = 0;
	private static float posZatual = 0;
	private static float posRatual = 0;

	private static float posXdestino = 0;
	private static float posYdestino = 0;
	private static float posZdestino = 0;
	private static float posRdestino = 0;

	private static float posXmov = 0;
	private static float posYmov = 0;
	private static float posZmov = 0;
	private static float posRmov = 0;

	private static final long serialVersionUID = 1L;

	private EnsaioConfig ensaio = new EnsaioConfig();

	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		HttpSession session = request.getSession();
		session.setAttribute("conexaoPorta", new Conexao());
		Conexao conexaoPorta = (Conexao) session.getAttribute("conexaoPorta");

	}

	private float deslocamento(float destino, float origem) {
		return destino - origem;
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		
		StringBuilder builder = new StringBuilder();
		

		BufferedReader reader = request.getReader();

		String line;
		while ((line = reader.readLine()) != null) {
			builder.append(line);

		}
		String data = builder.toString();

		System.out.println(data);

		Gson gson = new Gson();
		
		
		Posicao pos = gson.fromJson(data, Posicao.class);
		

		posXdestino = pos.xpos;
		posYdestino = pos.ypos;
		posZdestino = pos.zpos;
		posRdestino = pos.rpos;


		Posicao posi = new Posicao(deslocamento(posXdestino, posXatual),
				deslocamento(posYdestino, posYatual), deslocamento(posZdestino, posZatual),
				deslocamento(posRdestino, posRatual), pos.tempo, pos.operacao); // Receber da Interface WEB.




		
		
		if (posi.operacao.equals("zeraPeca") ) {
			System.out.println("zera peça");
			MovimentarMesa(request.getSession(), posi);
		}
		
		if (posi.operacao.equals("zeroMaquina" )) {
			System.out.println("zero maquina");
			ZeraMaquina(request);
		}
		if (posi.operacao.equals("movimentaMesa")) {
			System.out.println("Movimenta Mesa");
			MovimentarMesa(request.getSession(), posi);
		}
		

		posXatual = posXdestino;
		posYatual = posYdestino;
		posZatual = posZdestino;
		posRatual = posRdestino;

		System.out.println("destino: " + posXdestino);
		System.out.println("atual: " + posXatual);


		
		MovimentarMesa(request.getSession(), posi);


		MovimentarMesa(request.getSession(), pos);
		




	}

	public String LerTemperaturas(HttpSession session) {

		Conexao conexaoPorta = (Conexao) session.getAttribute("conexaoPorta");
		CommInterface inter = new CommInterface();

		inter.receber(conexaoPorta.entrada, conexaoPorta.saida, conexaoPorta.porta);

//		inter.receberTemp(conexaoPorta.entrada, conexaoPorta.saida, conexaoPorta.porta);

		return "";
	}

	public boolean MovimentarMesa(HttpSession session, Posicao posEnsaio) {

		boolean resp = false;

		Conexao conexaoPorta = (Conexao) session.getAttribute("conexaoPorta");
		CommInterface inter = new CommInterface();

		try {

			String teste = new Gson().toJson(posEnsaio);

			System.out.println("MovimentarMesa");
			inter.enviar(teste, conexaoPorta.saida, conexaoPorta.porta);
			Thread.sleep(posEnsaio.tempo);
			System.out.println(teste);
			inter.receber(conexaoPorta.entrada, conexaoPorta.saida, conexaoPorta.porta);

			resp = true;
		} catch (Exception e) {
			System.out.println("Error Post" + e.getMessage());
		}

		return resp;

	}

	public String convertString(BufferedReader entrada) {
		StringBuilder json = new StringBuilder();
		String linha = "";
		try {
			while ((linha = entrada.readLine()) != null) {
				json.append(linha);
			}
		} catch (Exception e) {
			return "";
		}
		return json.toString();
	}

	public void RepetirEnsaio(HttpServletRequest request, EnsaioConfig ensaio) {
		System.out.println("Entrei no repetir");
		for (Posicao pe : ensaio.posicoes) {
			MovimentarMesa(request.getSession(), pe);

			try {
				Thread.sleep(pe.tempo);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}

	}

	private void ZeraMaquina(HttpServletRequest request) {


		MovimentarMesa(request.getSession(), new Posicao(-1000, -1000, -1000, 0, 0, "zeraMaquina"));

	

	}

//	private EnsaioConfig ENSAIOCHUMBADAO() {
//		EnsaioConfig e = new EnsaioConfig();
//		e.nome = "Projeto ABC";
//		e.posicoes.add(new Posicao("-8", "-8", "-8", "0", 5000));
//		e.posicoes.add(new Posicao("8", "8", "8", "0", 5000));
//		e.posicoes.add(new Posicao("-8", "-8", "-8", "0", 5000));
//
//		return e;
//	}

}
