package br.senai.sp.model;

public class Posicao {
	
	public float xpos ;
	public float ypos ;
	public float zpos ;
	public float rpos ;
	public long tempo ;
	public String operacao;
	
	
	
	public Posicao() {
	
	}

	public Posicao(float xpos, float ypos, float zpos, float rpos, long tempo, String operacao) {
		super();
		this.xpos = xpos;
		this.ypos = ypos;
		this.zpos = zpos;
		this.rpos = rpos;
		this.tempo = tempo;
		this.operacao = operacao;
	}





}
