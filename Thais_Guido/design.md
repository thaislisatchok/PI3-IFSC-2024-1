# PI3-IFSC-2024-1

Projeto de um dispositivo para auxilio de pessoas com visão debilitada

Acesso rápido:

  - [Concepção](./concepção.md)
  - [Introdução](./README.md)
  - [Implementação](./implementação.md)
  - [Operação](./operação.md)

# Design 

O desenvolvimento do dispositivo seguiu um processo metódico e estruturado, visando garantir a funcionalidade, a integração eficaz dos componentes e a adaptação ao uso prático. O design do dispositivo foi abordado em várias etapas, desde a montagem inicial do circuito em uma protoboard até a finalização em uma placa de circuito impresso e a inserção em uma case protetora. A seguir, detalhamos cada etapa desse processo de design:

**1. Montagem Inicial do Circuito na protoboard**

Na fase inicial, a montagem do circuito foi feita em uma protoboard para realizar testes e ajustes preliminares. Esta etapa permitiu a validação dos componentes e a configuração do sistema. O processo incluiu os seguintes testes:

- **Testes Individuais dos Sensores Ultrassônicos:**
 
>* **Teste com um Sensor:** Iniciamos com a instalação de um único sensor ultrassônico para avaliar a capacidade de medição de distâncias. Foi verificada a precisão e o alcance do sensor em detectar obstáculos a diferentes distâncias.

>* **Teste com dois Sensores:** Em seguida, foram adicionados dois sensores ultrassônicos para analisar a cobertura e a precisão aumentada na detecção de obstáculos. Testamos a interação entre os sensores e a capacidade de fornecer informações mais detalhadas sobre o ambiente.

>* **Teste com três Sensores:** Finalmente, incorporamos os três sensores ultrassônicos, conforme o design final. Avaliamos a capacidade dos sensores de fornecer uma visão abrangente do ambiente, testando a precisão das medições e a capacidade de identificar a menor distância para priorizar a resposta do motor vibratório.

- **Teste Individual do Motor Vibratório:**

>* Realizamos testes individuais do motor vibratório para ajustar sua resposta tátil. Usamos diferentes tempos de delay para controlar a intensidade e o padrão de vibração. Este teste ajudou a calibrar o motor para fornecer feedback tátil adequado em resposta à proximidade dos obstáculos.

- **Integração Sensor e Motor:**

>* **Implementação Inicial:** Começamos integrando um sensor ultrassônico com o motor vibratório, avaliando como o motor respondia às distâncias medidas pelo sensor.

>* **Integração Completa:** Posteriormente, integramos os três sensores ultrassônicos com o motor vibratório. O sistema foi ajustado para que o motor vibrasse com base na menor distância detectada entre os sensores, indicando o obstáculo mais próximo e permitindo uma resposta tátil precisa para o usuário.

Abaixo, é possível visualizar imagens do circuito montado na protoboard, ilustrando a configuração inicial e os testes realizados.

![Protoboard](https://github.com/thaislisatchok/PI3-IFSC-2024-1/blob/main/Thais_Guido/imagens.md/protoboard1.jpeg)

![Protoboard](https://github.com/thaislisatchok/PI3-IFSC-2024-1/blob/main/Thais_Guido/imagens.md/protoboard2.jpeg)

![Protoboard](https://github.com/thaislisatchok/PI3-IFSC-2024-1/blob/main/Thais_Guido/imagens.md/protoboard3.jpeg)

