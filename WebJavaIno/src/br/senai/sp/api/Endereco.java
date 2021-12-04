package br.senai.sp.api;

public class Endereco {

	String logradouro;
    String bairro;
    String localidade;
    
    @Override
    public String toString() {
    	return  "Endereco = "+ "logradouro=" + logradouro + ", bairro=" + bairro + ", localidade=" + localidade;
    }
	public String getLogradouro() {
		return logradouro;
	}
	public void setLogradouro(String logradouro) {
		this.logradouro = logradouro;
	}
	public String getBairro() {
		return bairro;
	}
	public void setBairro(String bairro) {
		this.bairro = bairro;
	}
	public String getLocalidade() {
		return localidade;
	}
	public void setLocalidade(String localidade) {
		this.localidade = localidade;
	}
    
    
}
