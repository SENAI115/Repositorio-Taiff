package br.senai.sp.api;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import com.google.gson.Gson;

public class TesteAPI {
	   static String webService = "http://viacep.com.br/ws/";
	    static int codigoSucesso = 200;

	    public static Endereco buscaEnderecoPelo(String cep) throws Exception {
	        String urlParaChamada = webService + cep + "/json";  // Variavel com URI, endereco  e o final da URL

	        try {
	            URL url = new URL(urlParaChamada);
	            
	            HttpURLConnection conexao = (HttpURLConnection) url.openConnection();

	            if (conexao.getResponseCode() != codigoSucesso)
	                throw new RuntimeException("Error HTTP  : " + conexao.getResponseCode());

	            BufferedReader resposta = new BufferedReader(new InputStreamReader((conexao.getInputStream())));
	            String jsonEmString = Util.converteJsonEmString(resposta);

	            Gson gson = new Gson();
	            Endereco endereco = gson.fromJson(jsonEmString, Endereco.class);

	            return endereco;
	        } catch (Exception e) {
	            throw new Exception("ERROR: " + e);
	        }
	    }

}
