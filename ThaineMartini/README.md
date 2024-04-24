# Comandos, Aquisição e Armazenamento de dados de uma bancada de teste de um sistema de energia híbrido para drone

<p class="text-info recuo">
O mercado atual de drones, são raras as opções que possuem autonomia de voo maior que 50 minutos, fator esse que pode dificultar ou mesmo inviabilizar a realização de algumas missões. A marca mais conhecida do mercado (DJI) possui apenas uma opção comercial que promete atuar em uma margem maior de tempo que o limiar mencionado. Essa condição existe por conta das limitações de densidade energética dos armazenadores de energia disponíveis no mercado: baterias. Nesse contexto, uma opção viável para aumentar a autonomia consiste na utilização de conjuntos híbridos que podem ser embarcados na aeronave, utilizando um motor à combustão como parte do sistema de geração de energia elétrica.
</p>
<p class="text-info recuo">
Para implementar esse conjunto híbrido no drone, uma solução é importar sistemas pré-fabricados de geração de energia de outros países, como a China. Contudo a hipotética fabricação e nacionalização desse subsistema é uma solução interessante, haja vista o potencial de diminuição de custos, possibilidade de personalização da máquina e ausência dos trâmites de importação.
</p>

<p class="text-info recuo">
Para realizar esse projeto, foi desenvolvida uma bancada de testes pelo laboratório de drones do Instituto Federal de Ciência e Tecnologia de Santa Catarina (IFSC). O dispositivo consiste em um motor a combustão interna (MCI) acoplado a um motor BrushLess Direct Current (BLDC), que funciona como gerador de energia, e um retificador trifásico conectado à saída do gerador. Nessa configuração, o acelerador do motor à combustão possui um atuador eletromecânico (servo) que pode ser acionado eletronicamente por um sistema microcontrolado, que deve ajustar automaticamente e em tempo real a posição do acelerador conforme a energia demandada na saída o gerador trifásico (BLDC). Um dos principais desafios dessa simulação é desenvolver um sistema eletrônico de monitoramento e controle que mantenha a tensão constante mesmo com a variação da carga. Com o objetivo de desenvolver esse sistema de controle, é necessário projetar e confeccionar uma placa auxiliar que condiciona os sinais aferidos no sistema para um microcontrolador onde são tratados e armazenados em um log. Essa placa será desenvolvida no projeto integrador 3 e será detalhada a seguir.
</p>

<p class="text-info recuo">
Esse projeto integrador deve cumprir os seguintes requisitos, aferir e condicionar os sinais de RPM, temperatura do motor a combustão interna (MCI), corrente e tensão no barramento CC (pós-retificador) do sistema. Deve gerar dois sinais de pulse width modulation (PWM), um para o servo motor que acelera o MCI e outro para o driver que movimenta o BLDC para dar partida no motor. Esta placa também deve possuir dois conversores um de 12V e outro de 5V para a alimentação de payload e periféricos do drone. Assim como tem que gerar um arquivo de dados que contenha todos os sinais que foram monitorados. Na Figura 1, está delineado em formato de diagrama o projeto da PCI.
</p>
<div align="center">
Figura 1 - Diagrama do hardware
<img src="img/diagrama_hardware.jpg">
<figcaption>Fonte: Acervo pessoal</figcaption>
</div>

#### Cronograma idealizado 
<p> 12/03 - Cronograma </p>
<p> 20/03 - Levantamento dos componentes de projeto e pré requisitos </p>
<p> 27/03 - Levantamento dos componentes de projeto e pré requisitos </p>
<p> 03/04 - Esquemático da placa </p>
<p> 10/04 - Esquemático da placa </p>
<p> 17/04 - Layout da placa </p>
<p> 24/04 - Layout da placa </p>
<p> 08/05 - Fabricação da placa, documentação e programação do micro </p>
<p> 15/05 - Fabricação da placa, documentação e programação do micro </p>
<p> 22/05 - 1° TESTE e levantamento de log para análise </p>
<p> 29/05 - Ajustes </p>
<p> 05/06 - 2° TESTE e levantamento de log para análise </p>
<p> 12/06 - Ajustes </p>
<p> 19/06 - Apresentação </p>

## Desenvolvimento

### Componentes
<p> Os componentes foram selecionados de acordo com a disponibilidade no laboratório e com os requisitos o projeto </p>
<p> Servo motor: MG995, a aplicação necessita de um servo robusto e esse componente tem disponível no laboratório </p>
<p> UControlador: F280025C da Texas Instruments, um microcontrolador que aguenta o sistema de controle que será aplicado futuramente </p>
<p> Sensor de corrente: ACS758 150B, o máximo de corrente que o sensor terá que medir é de 80A, o sensor escolhido mede até 150A e tem disponivel no laboratório </p>
<p> Conversor CC/CC 48V - 5V: THL15-4811WL, robusto suficiente para aguentar os picos de tensão (até 60V) e tem disponivel no laboratório </p>
<p> Sensor de temperatura: NTC 33950 100k, o sensor deve medir pelo menos de 10 C até 200 C, o sensor escolhido mede de -4 a 270 C </p>
<p> Amplificador Opercional: TLV 9044 DIR, escolhido pela disponibilidade no laboratório </p>
<p> Regulador de Tensão: LM 1117 </p>

### Projeto
<p> O projeto foi realizado de acordo com diagrama de blocos demonstrado anteriormente</p>
#### Leitura da corrente

#### Leitura da tensão 
<p> Para a leitura da Tensão foi usado um divisor resistivo de tensão juntamente com um filtro Sallen-Key de segunda ordem (passa-baixa) para a diminuição de ruido na leitura do sinal</p>
### Esquemático 
### Layout
### Programação
