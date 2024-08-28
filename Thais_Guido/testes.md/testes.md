# PI3-IFSC-2024-1

Projeto de um dispositivo para auxilio de pessoas com visão debilitada

# Testes

A fase inicial de testes do protótipo é crucial para validar o funcionamento dos componentes e garantir que o dispositivo atende às expectativas em termos de desempenho, confiabilidade e usabilidade. Esta fase envolve tanto testes individuais dos componentes quanto testes integrados, onde todas as partes do sistema operam conjuntamente. Após a conclusão dessa fase, uma série de resultados e insights foram obtidos, permitindo avaliar o desempenho dos componentes individuais, a integração do sistema e a usabilidade geral do dispositivo.

1. **Sensores Ultrassônicos HC-SR04:** 

Cada sensor ultrassônico foi testado separadamente para verificar sua precisão na detecção de obstáculos. Isso inclui medir a distância mínima e máxima que o sensor pode detectar com precisão e garantir que os sinais de eco sejam recebidos e processados corretamente pelo microcontrolador. Durante os testes, foi confirmado que o módulo HC-SR04 oferece uma função de medição sem contato com um alcance que varia de 2 cm a 400 cm, com uma precisão de aproximadamente 3 mm. Esses módulos são compostos por um transmissor ultrassônico, um receptor e um circuito de controle integrado, que juntos possibilitam a detecção precisa de obstáculos.

- **Princípio de Operação do HC-SR04** : 

O funcionamento do HC-SR04 é relativamente simples e direto. O módulo emite um pulso ultrassônico de 40 kHz que, ao encontrar um obstáculo, reflete e retorna ao receptor do módulo. O tempo de viagem desse pulso ultrassônico, somado à velocidade do som, permite calcular a distância entre o sensor e o obstáculo com alta precisão.

* **Procedimento de Operação**:

De acordo com a folha de dados do HC-SR04, o seguinte procedimento deve ser seguido para obter medições precisas:

>* **Ativação do Sinal Trig:** O pino Trig deve ser mantido em nível ALTO (HIGH) por pelo menos 10 microsegundos (us). Esse comando inicia o processo de medição.

>* **Emissão e Detecção de Pulso:** Após receber o comando, o módulo emite 8 ciclos de ultrassom a 40 kHz. Ele então monitora se há um sinal refletido de volta ao receptor. Se um obstáculo for detectado, o módulo gera um PULSO ALTO no pino Echo. 

>* **Cálculo da Distância:** A largura desse PULSO ALTO é proporcional à distância do objeto detectado. A distância pode ser calculada utilizando a fórmula:











>* *Tempo de espera:** Após cada medição, é recomendável aguardar pelo menos 60 ms antes de iniciar a próxima operação. Isso garante que o módulo esteja pronto para a próxima medição sem interferências ou erros.




2. **Microcontrolador STM32F103C8:** Os testes iniciais do microcontrolador envolveram verificar se ele estava recebendo e processando corretamente os sinais dos sensores. Também se testa a programação dos algoritmos de detecção e controle, garantindo que o microcontrolador possa tomar decisões em tempo real, como quando ativar o feedback tátil.

3. **Motor Vibratório:** O motor foi testado para garantir que ele fornecesse diferentes níveis de vibração com base nos comandos do microcontrolador. A intensidade e a duração da vibração serão calibradas para serem perceptíveis, mas não desconfortáveis, ao usuário.

