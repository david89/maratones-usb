maratones-usb
=============

Repositorio usado para los maratones de programación de la Universidad Simón Bolívar. Acá podremos discutir y hacer revisiones de código de los problemas que serán usados en los locales.

formato-problemas
=================

Vamos a ver si con este formato se puede automatizar un poco la generación de los problemsets.

    year/
      problem-1/
        problem-1.{java, c, cpp}
        problem-1-i.in
        problem-1-i.out
        problem-statement.{txt, tex}
        problem-solution.{txt, tex}
        generator/
          script-problem-1.{*}
          input/
            handmade-test-cases
            other-files
          output/
            problem-1-i.in
            problem-1-i.out
      problem-2/
        ...
      ...
