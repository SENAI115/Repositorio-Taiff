/**
 * 
 */

var xpos = 0;
var ypos = 0;
var zpos = 0;
var rpos = 0;
var decisao;
var memoriaPosicao = [];
var url = 'http://localhost:8080/WebJavaIno/WebJava';


var posx;
var posy;
var posz;
var posr;
var tempo;
var operacao;

// ------------------------------------------------------------------------ //


function zeroPeca() {

	operacao = "zeraPeca";

	enviar();

}

function zeraMaquina() {

	operacao = "zeroMaquina";

	console.log(operacao);

	enviar();

}






function enviar() {


	posx = document.getElementById("xpos").value;
	posy = document.getElementById("ypos").value;
	posz = document.getElementById("zpos").value;
	posr = document.getElementById("rpos").value;
	tempo = document.getElementById("tempo").value;

	console.log("operacao: " + operacao);

	send(posx, posy, posz, posr, tempo, operacao);

	let btns = document.getElementsByClassName("button");

	for (let i = 0; i < btns.length; i++) { btns[i].disabled = true }
	setTimeout(() => { for (let i = 0; i < btns.length; i++) { btns[i].disabled = false } }, 3000);

}

function enviarMovimentaMesa() {


	posx = document.getElementById("xpos").value;
	posy = document.getElementById("ypos").value;
	posz = document.getElementById("zpos").value;
	posr = document.getElementById("rpos").value;
	tempo = document.getElementById("tempo").value;

	console.log("operacao: " + operacao);

	send(posx, posy, posz, posr, tempo, "movimentaMesa");

	}
	
	
	
	

	function verifica(eixoX, eixoY, eixoZ, eixoR, tempo) {


		console.log("Verifica");

		if (eixoX == null || isNaN(eixoX)) {
			posx = 0;
			document.getElementById("xpos").value = posx;
		}
		if (eixoY == null || isNaN(eixoY)) {
			posy = 0;
			document.getElementById("ypos").value = posy;
			console.log(posy);
			console.log("entrei y");
		}
		if (eixoZ == null || isNaN(eixoZ)) {
			posz = 0;
			document.getElementById("zpos").value = posz;
		}
		if (eixoR == null) {
			posr = 0;
			document.getElementById("rpos").value = posr;
		}
		if (tempo == null) {
			tempo = 0;
			document.getElementById("tempo").value = tempo;
		}

	}


	function construtor() {

			fetch(url, {method: 'GET'})
				.then(function(data) {
					console.log('Request success: ', data);
				})
				.catch(function(error) {
					console.log('Request failure: ', error);
				});

			removeConstrutor();

			alert("Conectado com o Arduino!!!");

		}

		function removeConstrutor() {
			var elem = document.getElementById('construtor-do-bitt');
			elem.parentNode.removeChild(elem);
			return false;
		}

		function movimentaMesa(valormais, sinal, elemento) {


			console.log(operacao);
			document.getElementsByClassName(elemento).disabled = true;

			setTimeout(() => document.getElementsByClassName(elemento).disabled = false, 2000);

			let idPos = "";
			if (valormais == 'x')
				idPos = "xpos";
			else if (valormais == 'y')
				idPos = "ypos";
			else if (valormais == 'z') {
				idPos = "zpos";
			}
			else if (valormais == 'r')
				idPos = "rpos";

			let inputt = document.getElementById(idPos).value;
			if (inputt == '')
				inputt = '0';

			inputt = parseInt(inputt);

			if (sinal == '+')
				inputt++;
			else if (sinal == '-')
				inputt--;
			else if (sinal == '+10')
				inputt = inputt + 10;
			else if (sinal == '-10')
				inputt = inputt - 10;

			document.getElementById(idPos).value = inputt;


			enviarMovimentaMesa();

			let btns = document.getElementsByClassName("button");

			for (let i = 0; i < btns.length; i++) { btns[i].disabled = true }
			setTimeout(() => { for (let i = 0; i < btns.length; i++) { btns[i].disabled = false } }, 3000);
		};


		// -----------------------------------------

		function send(posx, posy, posz, posr, tempo, operacao) {

			let controller = new AbortController();
			setTimeout(() => controller.abort(), 100);
			fetch(url, {
				signal: controller.signal,
				method: 'POST',
				body: JSON.stringify({

					xpos: posx,
					ypos: posy,
					zpos: posz,
					rpos: posr,
					tempo: tempo,
					operacao: operacao
				})
			}).then(function(data) {
				console.log('Request success: ', data);
			})
			.catch(function(error) {
				console.log('Request failure: ', error);
					});
		}
				
									
