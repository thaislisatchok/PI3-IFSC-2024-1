# PI3-IFSC-2024-1

Projeto de um dispositivo para auxilio de pessoas com visão debilitada

Acesso rápido:  
  - [Introdução](./README.md)
  - [Concepção](./concepção.md)
  - [Design/Projeto](./design.md)
  - [Operação](./operação.md)

# Implementação 

Nesta seção, detalharemos a implementação do sistema desenvolvido para melhorar a mobilidade e a segurança de pessoas com deficiência visual. A implementação abrange a configuração do microcontrolador STM32F103C8, a integração dos sensores ultrassônicos e do motor vibratório, e a programação necessária para a operação do dispositivo.

Inicialmente, a fase de testes do protótipo foi fundamental para validar o funcionamento dos componentes e garantir que o dispositivo atende às expectativas em termos de desempenho, confiabilidade e usabilidade. Essa fase incluiu testes tanto dos sensores ultrassônicos HC-SR04 quanto do motor vibratório, permitindo avaliar o desempenho individual dos componentes, a integração do sistema e a usabilidade geral do dispositivo.

1. **Sensores Ultrassônicos HC-SR04:** 

Cada sensor ultrassônico foi testado separadamente para verificar sua precisão na detecção de obstáculos. Os testes incluíram medir a distância mínima e máxima que cada sensor pode detectar com precisão e garantir que os sinais de eco fossem recebidos e processados corretamente pelo microcontrolador.

- **Resultados dos Testes:** Durante os testes, foi confirmado que o módulo HC-SR04 oferece uma função de medição sem contato com um alcance que varia de 2 cm a 400 cm, com uma precisão de aproximadamente 3 mm. Esses módulos são compostos por um transmissor ultrassônico, um receptor e um circuito de controle integrado, que juntos possibilitam a detecção precisa de obstáculos.

- **Princípio de Operação do HC-SR04:** O funcionamento do HC-SR04 é relativamente simples e direto. O módulo emite um pulso ultrassônico de 40 kHz que, ao encontrar um obstáculo, reflete e retorna ao receptor do módulo. O tempo de viagem desse pulso ultrassônico, combinado com a velocidade do som, permite calcular a distância entre o sensor e o obstáculo com alta precisão.

- **Procedimento de Operação**: De acordo com a folha de dados do HC-SR04, o seguinte procedimento foi seguido para obter medições precisas:

>* **Ativação do Sinal Trig:** O pino Trig deve ser mantido em nível ALTO (HIGH) por pelo menos 10 microsegundos (us). Esse comando inicia o processo de medição.

>* **Emissão e Detecção de Pulso:** Após receber o comando, o módulo emite 8 ciclos de ultrassom a 40 kHz. Ele então monitora se há um sinal refletido de volta ao receptor. Se um obstáculo for detectado, o módulo gera um PULSO ALTO no pino Echo. 

>* **Cálculo da Distância:** A largura desse PULSO ALTO é proporcional à distância do objeto detectado. A distância pode ser calculada utilizando a fórmula:

**alcance = tempo de alto nível * velocidade do som (340 m/s) / 2**

Alternativamente, pode-se usar fórmulas simplificadas:

**distância em cm= tempo de alto nível em microssegundos/58**

ou

**distância em polegada= tempo de alto nível em microssegundos/148**

>* **Tempo de espera:** Após cada medição, é recomendável aguardar pelo menos 60 ms antes de iniciar a próxima operação. Isso garante que o módulo esteja pronto para a próxima medição sem interferências ou erros.
>
## *MÉTODO DE PULSO ALTO(ou alto nível)*

No funcionamento do módulo HC-SR04, o processo de medição de distância envolve a emissão de pulsos ultrassônicos e a detecção de seu retorno. Quando o pino Trig é mantido em nível ALTO por pelo menos 10 microsegundos (µs), o módulo inicia a emissão de um pulso ultrassônico. Esse pulso é gerado em 8 ciclos de ondas ultrassônicas com uma frequência de 40 kHz. Esses 8 ciclos formam o pulso ultrassônico que viaja pelo ar e reflete em obstáculos. O tempo total que o pulso leva para retornar ao módulo é detectado pelo pino Echo, que gera um pulso ALTO cuja largura é proporcional ao tempo de ida e volta do sinal. Assim, a distância é calculada conforme a fórmula citada anteriormente. Para uma compreensão mais clara do funcionamento, consulte a ilustração abaixo, que demonstra detalhadamente o processo de emissão dos 8 ciclos de pulso ultrassônico e a medição do tempo de retorno.

![Pulso](https://github.com/thaislisatchok/PI3-IFSC-2024-1/blob/main/Thais_Guido/imagens.md/pulso.png)

### **Desempenho nos Testes Práticos**

Durante os testes, o HC-SR04 demonstrou um desempenho confiável em diversas condições. Em ambientes fechados, o sensor forneceu medições consistentes e precisas, mesmo com superfícies de diferentes materiais e texturas. Em ambientes abertos, o sensor manteve sua precisão, embora superfícies muito reflexivas ou absorventes pudessem alterar levemente as medições, o que é uma característica conhecida desse tipo de sensor.

2. **Microcontrolador STM32F103C8:**

Os testes iniciais do microcontrolador STM32F103C8 incluíram diversas etapas para garantir o correto funcionamento do sistema. Inicialmente, verificou-se se o microcontrolador estava recebendo e processando adequadamente os sinais dos sensores ultrassônicos. Isso envolveu a implementação de rotinas básicas para a leitura dos dados dos sensores e a verificação dos sinais recebidos através de portas de entrada/saída (I/O). Além disso, foram realizados testes para assegurar que os algoritmos de detecção e controle, que são responsáveis por processar as informações dos sensores e tomar decisões, estavam funcionando conforme o esperado. Isso incluiu a programação de interrupções e timers para lidar com as medições dos sensores em tempo real.
Os testes também garantiram que o microcontrolador pudesse ativar o feedback tátil (motor vibratório) com precisão e no momento certo, com base nas informações dos sensores. O microcontrolador foi configurado para processar os dados dos sensores e gerar sinais de controle que acionam o motor vibratório, fornecendo feedback ao usuário sobre a proximidade dos obstáculos.

Além disso, foram testadas a comunicação entre o microcontrolador e outros componentes do sistema, como a correta integração do driver do motor e a resposta adequada aos comandos de controle. O desempenho do microcontrolador foi avaliado em diferentes condições operacionais para garantir que ele pudesse operar de forma confiável e responder a mudanças no ambiente em tempo real.

Os testes iniciais ajudaram a validar a capacidade do STM32F103C8 em gerenciar as tarefas do sistema e a garantir a precisão e confiabilidade do protótipo, resultando em um dispositivo funcional e eficiente para a detecção de obstáculos e feedback tátil.

3. **Motor Vibratório:** 

O motor vibratório foi testado para assegurar que ele respondesse corretamente aos comandos enviados pelo microcontrolador STM32F103C8 através do código programado no STM32CubeIDE. Durante os testes, verificou-se que o motor fornecia diferentes níveis de vibração conforme os comandos recebidos, permitindo que a intensidade e a duração da vibração fossem ajustadas de acordo com a proximidade dos obstáculos detectados pelos sensores ultrassônicos.
Foi realizada uma calibração detalhada para garantir que a vibração fosse perceptível ao usuário, mas não causasse desconforto. Isso envolveu ajustar o PWM (Pulse Width Modulation) gerado pelo microcontrolador. O PWM foi configurado utilizando um canal de timer no STM32F103C8, onde a largura do duty cycle foi ajustada para controlar a intensidade da vibração do motor. O duty cycle determina a proporção de tempo em que o sinal de controle está em nível ALTO durante cada ciclo de PWM, afetando diretamente a força da vibração.

O funcionamento do motor vibratório foi monitorado para garantir que o sinal PWM do microcontrolador fosse aplicado corretamente e que a resposta do motor fosse consistente e conforme o esperado. Os testes incluíram a verificação da resposta do motor a diferentes duty cycles e a análise de como essas variações influenciam a sensação de vibração para o usuário. Este processo garantiu que o motor vibratório fornecesse feedback tátil adequado, melhorando a eficácia do dispositivo como um todo.