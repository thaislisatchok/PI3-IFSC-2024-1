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
Figura 1
<img src=“img/diagrama_hardware.jpg”>
<figcaption>Fonte: Acervo pessoal</figcaption>
