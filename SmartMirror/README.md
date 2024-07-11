<table align="center"><tr><td align="center" width="9999"><br>
<img src="logoifsc.png" align="center" width="150" alt="Logo IFSC">

# Smart Mirror

<b><br>Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina<br>
Campus Florianópolis<br>
Departamento Acadêmico de Eletrônica<br>
Projeto Integrador III</b>

*Jonathan Chrysostomo Cabral Bonette*<br>
*Alexsander Vieira*

#

Os espelhos inteligentes são dispositivos integrados com funcionalidades interativas e personalizáveis, projetados para oferecer uma variedade de serviços e informações enquanto os usuários se preparam para o dia ou executam tarefas cotidianas em frente ao espelho. Assim como as residências inteligentes, esses espelhos representam uma tendência em ascensão nos últimos anos, combinando tecnologia e praticidade para criar um ambiente mais confortável e conveniente.

Esses dispositivos conectados são capazes de fornecer não apenas reflexos, mas também uma gama de recursos úteis, como acesso a informações sobre o clima, notícias, calendário e até mesmo controle de dispositivos domésticos conectados. Por exemplo, ao se aproximar do espelho pela manhã, os usuários podem ser recebidos com as últimas notícias, previsão do tempo e lembretes de compromissos do dia, tudo enquanto se preparam para enfrentar as atividades diárias.

De acordo com dados divulgados pelo site Techaeris, quase 70% dos americanos acreditam que, em cerca de uma década, as residências inteligentes serão tão difundidas quanto os smartphones. Adicionalmente, mais de 80% dos potenciais compradores de imóveis consideram as casas inteligentes como uma das suas principais preferências.

Seguindo a tendência das smart homes, os espelhos inteligentes oferecem uma experiência personalizada e conveniente, permitindo que os usuários controlem diversos aspectos de sua rotina diária sem sair do lugar. Com a capacidade de integração com outros dispositivos domésticos inteligentes, como sistemas de iluminação e termostatos, esses espelhos se tornam parte essencial de um ecossistema conectado, contribuindo para uma vida mais eficiente e tecnologicamente avançada.

</td></tr></table>

# Idealização do Projeto

A essência dos espelhos inteligentes reside na sua capacidade de incorporar tecnologia avançada até mesmo em objetos cotidianos, como os próprios espelhos. Esses dispositivos representam uma revolução no conceito de residências conectadas, oferecendo uma conveniência incomparável em atividades simples do dia a dia, como se preparar para enfrentar o mundo lá fora.

Imagine acordar de manhã, e ao primeiro sinal movimentação em frente ao espelho seu espelho se ilumina suavemente e enquanto você se prepara, seu espelho inteligente não apenas reflete sua imagem, mas também atua como um hub de informações vitais para o seu dia. Com apenas um olhar, você fica sabendo das condições climáticas, seus compromissos agendados, e as principais notícias do momento, tudo isso sem sequer tocar em um dispositivo.

E não para por aí. Com um simples toque na superfície do espelho ou um comando de voz ou até mesmo gestos, você pode interagir com sua casa de maneira intuitiva e sem esforço. Quer saber se alguém está na sua casa enquanto você está fora? Ou talvez ajustar a temperatura do ambiente ou reproduzir sua playlist favorita? Tudo isso é possível graças à integração perfeita entre o espelho inteligente e os demais dispositivos conectados em sua residência.

O objetivo deste projeto é justamente explorar essas possibilidades e oferecer uma experiência centralizada para o usuário. Acender a luz do quarto, verificar a temperatura, checar sua agenda, ou até mesmo ligar uma câmera de segurança, tudo isso ao alcance de um simples espelho, proporcionando um vislumbre do futuro, ou melhor, do presente.

# Itens Utilizados (Hardware e Componentes)

***listar as imagens e informações relacionadas ao hardware***

• Tela (televisão ou monitor com caixinha de som para reprodução sonora).<br>
• Placa de desenvolvimento (raspberry pi pelo poder de processamento necessário).<br>
• Sensores de movimentos (MGC3130, GP2Y0A21YK, PAJ7620u2, APDS9960, PiCamera*).<br>
• Moldura IR.<br>
• Entre outros.<br>

***listar as imagens e informações relacionadas ao hardware***

• 1. Organizar os pré requisitos necessários<br>
• 2. Configurar o sistema operacional (Raspbian)<br>
• 3. Instalar e configurar o servidor back-end (Node.js)<br>
• 4. Desenvolver e configurar a interface front-end (JavaScript)<br>
• 5. Desenvolver os blocos necessários para a nossa aplicação<br>
• 6. Conectar e configurar as APIs necessárias para os blocos<br>
• 7. Testar e aprimorar a funcionalidade dos blocos sem os recursos de sensores<br>
• 8. Implementar os recursos de sensores, alimentar as informações e integrar nos blocos já existentes<br>
• 9. Documentar<br> (***adicionar fluxograma***)

# Itens Utilizados (Software)

***listar as imagens e informações relacionadas ao software***

• linguagens de programação como JavaScript, Node.js, e frameworks para desenvolvimento de interfaces.<br>
• JavaScript para configurar a interface front web.<br>
• Node para configurar o back end e os módulos necessários.<br>
• API’s diversas para os funcionamentos dos módulos.<br>
• Raspbian (OS do raspberry pi).<br>

***listar as imagens e informações relacionadas ao software***

• 1. Organizar os pré requisitos necessários<br>
• 2. Selecionar e adquirir os componentes de hardware necessários<br>
• Tela (televisão ou monitor)<br>
    • Placa de desenvolvimento (Raspberry Pi)<br>
    • Sensores<br>
    • Moldura IR (se necessário)<br>
• 3. Montar os componentes de hardware<br>
• 4. Integrar o hardware com o software<br>
• 5. Testar e aprimorar a funcionalidade do sistema integrado<br>
• 6. Documentar<br> (***adicionar fluxograma***)

# Conceito

***listar as imagens e informações***

# Design

***listar as imagens e informações***

# Implementação

***listar as imagens e informações***

# Operação

***listar as imagens e informações***

# Resultados

***listar as imagens e informações***

# Percepções Pessoais e Considerações Finais

***listar as imagens e informações***

• Prototipagem iterativa para testar e aprimorar o produto ao longo do processo de desenvolvimento.<br>
• Substituição do sensor APDS9960 pelo PAJ7620U2 devido seu sensor melhor (***adicionar informações comparativas***).<br>
• Pelas pesquisas a Pi Camera parece ter uma capacidade de visão computacional bem maior que os módulos básicos de gestão de movimentos, onde juntamente com o módulo OpenCV ela consegue trackear até mesmo todas as juntas da mão, dando uma possibilidade bem maior no desenvolvimento de aplicabilidades para o espelho inteligente. Custo elevado (R$ 250,00).<br>
• * O uso do televisor é interessante pois já tem a saída de áudio, caso formos usar um monitor de computador precisamos usar uma caixa de som externa.<br>
• * O uso da moldura de madeira talvez não seja necessário dependendo do custo, mas teríamos que substituir por um vidro inteiro.<br>
• * O uso das API’s vai depender do que vamos querer implementar.<br>
• Durante a compra do APDS9960 foi identicado um erro que não o fazia funcionar, durante extensas pesquisas, soube-se que o sensor era de origem chinesa, dito isso, tivemos que modificar seu arquivo base (SparkFun_APDS9960.h), onde tivemos que modificar o hexadecimal da #define APDS9960_ID_1 0xAB, para #define APDS9960_ID_1 0xA8, fazendo o sensor funcionar corretamente. (***adicionar imagem***)<br>
• No raspberry pi os desafios são constantes, durante o desenvolvimento do módulo de sensor de movimentos, tivemos que habilitar a porta i2c e ajustar o baudrate do raspberry para a detecção correta do sensor, a partir desta etapa utilizando o comando (sudo i2cdetect -y 1) podemos ver agora que o sensor é visivel pelos pinos do raspberry pi. (***adicionar imagem***)<br>
• Também devido as documentações dos módulos estarem um pouco desatualizadas, foi preciso um esforço extenso analisando os códigos para refatorar as partes onde outrora estavam desatualizadas. Foram adicionados logs de mensagens no terminal para um debugger mais eficiente. (***adicionar imagem***)


