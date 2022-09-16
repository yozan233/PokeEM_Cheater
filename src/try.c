u16 S=SelectItem;
u8 a=0,i=0;
while(a < 3){ //b0 a=1,b0 a=1,b0 b1 a=2,b0 b1 a=2
    S--;    //b0 a=1,b0 a=1,b0 b1 a=2,b0 b1 a=2, b0 b1 b2 a=3
    u8 itemN = getItemNmae(S);
    if (itemN == 0)
        break;
    else if(itemN != 1){
             setbuffer(i,S);
             a++;
             i++;
         }
}
i++;
setbuffer(i,SelectItem); //b0 b1 b2 b3

u8 b = 3;
if(a < 3)
    b = 6-a;
S=SelectItem;
while(b){ //b3 b=3,b3 b=3,b3 b=3,b3 b4 b=2,b3 b4 b5 b=1,b3 b4 b5 b6 b=0
    S++; //b4 b=2, b4 b5 b=1
    u8 itemN = getItemNmae(S);
    if (itemN == 0)
        break;
    else if(itemN != 1){
            setbuffer(i,S);
            b--;
            i++;
        }
}
if(b){
    a = 3 -b;
    右移(7-a);
    S = b0;
    i = 0;
    while(a){
        S--;
        u8 itemN = getItemNmae(S);
        if (itemN == 0)
                break;
            else if(itemN != 1){
                    setbuffer(i,S);
                    a--;
                    i++;
                }
    }
}
for(k=0;k<7;k++){
    u16 Na = getbuffer;
    if(Na == SelectItem)
    {
        strbData->attackN = 0xFFEF;
		print_text(148,k*18+16,&strbData->attackN);
    }
    print_text(156,k*18+16,getItemNmae(Na));//中
}


        A
1 2 3 4 5 6 7
a = 4,b =2;

b0 b1 b2 b3 b4 b5 b6
2  3  4  5  6  7
2  2  3  4  5  6  7

    A
1 2 3 4 5 6 7
a = 2,b = 4

b0 b1 b2 b3 b4 b5 b6
1  2  3  4  5  6  

u16 S=3;
			u8 a6=0,i6=0;
			while(a6 < 3){
				S--;
				u8 itemN = getItemName(S);
				if (itemN == 0)
					break;
				else if(itemN != 1){
						setbuffer(i6,S);
						a6++;
						i6++;
					}
			}
			i6++;
			setbuffer(i6,3);

			u8 b6 = 3;
			if(a6 < 3)
				b6 = 6-a6;
			S=3;
			while(b6){
				S++;
				u8 itemN = getItemName(S);
				if (itemN == 0)
					break;
				else if(itemN != 1){
						setbuffer(i6,S);
						b6--;
						i6++;
					}
			}
			if(b6){
				a6 = 3 -b6;
				//右移(a6);
				bufferMove(7-a6);
				S = b0;
				i6 = 0;
				while(a6){
					S--;
					u8 itemN = getItemName(S);
					if (itemN == 0)
							break;
						else if(itemN != 1){
								setbuffer(i6,S);
								a6--;
								i6++;
							}
				}
			}
			for(k=0;k<7;k++){
				u16 Na = getbuffer(k);
				if(Na == 3)
				{
					strbData->attackN = 0xFFEF;
					print_text(148,k*18+16,&strbData->attackN);
				}
				print_text(30,k*18,getItemName(Na));//中
			}


            