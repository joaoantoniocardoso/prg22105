// while(!feof(fp)){
//   // Carrega os dados do resistor.
//   fscanf(fp, "%f %f %f %f %f", &val, &sre, &err, &pwr, &qtd);
//   
//   // Insere ele na lista apenas se não for nulo.
//   if(val && sre && err && pwr && qtd)
//   {
// 
//     // Cria os dados na ordem inversa para conseguir linkar os filhos.
//     // Os filhos são sempre listas ou árvores, mas mantém-se uma referência
//     // para cada nível utilizando um cabeçalho de lista. No fim teremos
//     // listas de listas de listas de árvores binárias, ou seja, uma árvore 
//     // heterogênea ordenada, e possivelmente desbalanceada.
//     getchar();
//     lsre = lerr = lpwr = ltmp = NULL; // Zera as temporárias (precaução)
//     if((ltmp = searchList(lhsre, sre))){							// Se sre
//     	lsre = ltmp;																			// Seleciona a lista lsre
//     	if((ltmp = searchList(lherr, err))){						// Se err
//     		lerr = ltmp;																		// Seleciona a lista lerr
//     		if((ltmp = searchList(lhpwr, pwr))){					// Se pwr
//     			lpwr = ltmp;																	// Seleciona a lista lpwr
//     			tval = insertTree(tval, val, qtd);						// Insere nó
//     			(*lpwr).child = tval;													// Associa tval à lpwr
//     			(*lerr).child = lpwr;													// Associa lpwr à lerr
//     			(*lsre).child = lerr;													// Associa lerr à lsre
//     			
//     			printf("1:\n");
//     		}
//     		else{																					// Se !pwr
//     			tval = NULL;																	// Seleciona uma nova árvore
//     			tval = insertTree(tval, val, qtd);						// Insere nó
//     			lpwr = insertList(lhpwr, pwr, tval);					// Cria e Insere lpwr com filho tval
//     			(*lerr).child = lpwr;													// Associa lpwr à lerr
//     			(*lsre).child = lerr;													// Associa lerr à lsre
//     			
//     			printf("2:\n");
//     		}
//     	}
//     	else{																						// Se !err,(e !pwr)
//     		tval = NULL;																		// Seleciona um nó nulo
//     		tval = insertTree(tval, val, qtd);							// Insere nó
//     		lpwr = insertList(lhpwr, pwr, tval);						// Cria e Insere lpwr com filho tval
//     		lerr = insertList(lherr, err, lpwr);						// Cria e Insere lerr com filho lpwr
//     		(*lsre).child = lerr;														// Associa lerr à lsre
//     		
//     		printf("3:\n");
//     	}
//     }
//     else{																							// Se !sre,(!err e !pwr)
//     	tval = NULL;																			// Seleciona um nó nulo
//     	tval = insertTree(tval, val, qtd);								// Insere nó
//     	lpwr = insertList(lhpwr, pwr, tval);							// Insere pwr com filho tval
//     	lerr = insertList(lherr, err, lpwr);							// Insere lerr com filho lpwr
//     	lsre = insertList(lhsre, sre, lerr);							// Insere lsre com filho lerr
//     	
//     	printf("4:\n");
//     }
//     
//     
//     #ifdef DEBUG
//       printf(": \t(lhsre)0x%016lx\t(lherr)0x%016lx\t(lhpwr)0x%016lx\n", (unsigned long)lhsre, (unsigned long)lherr, (unsigned long)lhpwr);
//       printf(": \t(shsre)0x%016lx\t(sherr)0x%016lx\t(shpwr)0x%016lx\n", (unsigned long)(*lhsre).start, (unsigned long)(*lherr).start, (unsigned long)(*lhpwr).start);
//       printf(": \t\t\t\t\t( lerr)0x%016lx\t( lpwr)0x%016lx\t( tval)0x%016lx\n", (unsigned long)lerr, (unsigned long)lpwr, (unsigned long)tval);
//       printf(": \t(clsre)0x%016lx\t(clerr)0x%016lx\t(clpwr)0x%016lx\n", (unsigned long)(*lsre).child, (unsigned long)(*lerr).child, (unsigned long)(*lpwr).child);
//       printf(": \t(  sre)%.2f\t\t(  err)%.2f\t\t(  pwr)%.2f\t\t(  val)%.2f\n", sre, err, pwr, val);
//       
//       printTree(tval);
//       putchar('\n');
//       printList(lhsre);
//       printList(lherr);
//       printList(lhpwr);
//     #endif
//     #ifdef VERBOSE
//       printAll(lhsre);
//     #endif
//     
//     // #ifdef VERBOSE 
//     // 	int a = 0;
//     // 	if(a>=25){
//     // 		// system(CLEAR);
//     // 		printf("Carregando... \n");
//     // 		a=0;
//     // 	}a++;
//     // 	printf("%f %f %f %f %f\n",
//     // 		sre, 
//     // 		err, 
//     // 		pwr, 
//     // 		val, 
//     // 		qtd
//     // 	);
//     // #endif
//   }
// }