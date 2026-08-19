#ifndef ARGS_C
#define ARGS_C
#include "args.h"

str_t arg_strings[] = {
	(str_t){.len=2,.str="-h"},
	(str_t){.len=6,.str="-help"},
	(str_t){.len=2,.str="-v"},
	(str_t){.len=9,.str="-version"},
	(str_t){.len=2,.str="-i"},
	(str_t){.len=7,.str="-input"},
	(str_t){.len=3,.str="-dh"},
	(str_t){.len=7,.str="-height"},
	(str_t){.len=3,.str="-dw"},
	(str_t){.len=6,.str="-width"},
	(str_t){.len=2,.str="-b"},
	(str_t){.len=7,.str="-border"},
	(str_t){.len=3,.str="-bl"},
	(str_t){.len=12,.str="-border-left"},
	(str_t){.len=3,.str="-br"},
	(str_t){.len=13,.str="-border-right"},
	(str_t){.len=3,.str="-bu"},
	(str_t){.len=10,.str="-border-up"},
	(str_t){.len=3,.str="-bd"},
	(str_t){.len=12,.str="-border-down"},
	(str_t){.len=3,.str="-bc"},
	(str_t){.len=13,.str="-border-color"},
	(str_t){.len=3,.str="-lc"},
	(str_t){.len=11,.str="-line-color"},
	(str_t){.len=3,.str="-ac"},
	(str_t){.len=11,.str="-axis-color"},
	(str_t){.len=3,.str="-cc"},
	(str_t){.len=11,.str="-char-color"},
	(str_t){.len=3,.str="-vc"},
	(str_t){.len=11,.str="-view-color"},
	(str_t){.len=3,.str="-xs"},
	(str_t){.len=8,.str="-x-start"},
	(str_t){.len=3,.str="-ys"},
	(str_t){.len=8,.str="-y-start"},
	(str_t){.len=3,.str="-xe"},
	(str_t){.len=6,.str="-x-end"},
	(str_t){.len=3,.str="-ye"},
	(str_t){.len=6,.str="-y-end"},
	(str_t){.len=3,.str="-xr"},
	(str_t){.len=8,.str="-x-range"},
	(str_t){.len=3,.str="-yr"},
	(str_t){.len=8,.str="-y-range"},
	(str_t){.len=3,.str="-xp"},
	(str_t){.len=10,.str="-x-padding"},
	(str_t){.len=3,.str="-yp"},
	(str_t){.len=10,.str="-y-padding"},
	(str_t){.len=3,.str="-xl"},
	(str_t){.len=8,.str="-x-lines"},
	(str_t){.len=3,.str="-yl"},
	(str_t){.len=8,.str="-y-lines"},
	(str_t){.len=5,.str="-xlsy"},
	(str_t){.len=11,.str="-x-lines-sy"},
	(str_t){.len=5,.str="-ylsx"},
	(str_t){.len=11,.str="-y-lines-sx"},
	(str_t){.len=3,.str="-cs"},
	(str_t){.len=10,.str="-char-size"},
	(str_t){.len=3,.str="-lw"},
	(str_t){.len=11,.str="-line-width"},
	(str_t){.len=4,.str="-alw"},
	(str_t){.len=16,.str="-axis-line-width"},
	(str_t){.len=4,.str="-xff"},
	(str_t){.len=16,.str="-x-figure-format"},
	(str_t){.len=4,.str="-yff"},
	(str_t){.len=16,.str="-y-figure-format"},
	(str_t){.len=3,.str="-ff"},
	(str_t){.len=14,.str="-figure-format"},
	(str_t){.len=4,.str="-sxl"},
	(str_t){.len=14,.str="-show-x-lines"},
	(str_t){.len=4,.str="-syl"},
	(str_t){.len=14,.str="-show-y-lines"},
	(str_t){.len=3,.str="-sl"},
	(str_t){.len=11,.str="-show-lines"},
	(str_t){.len=4,.str="-dl"},
	(str_t){.len=16,.str="-dashed-line"},
	(str_t){.len=4,.str="-sxa"},
	(str_t){.len=12,.str="-show-x-axis"},
	(str_t){.len=4,.str="-sya"},
	(str_t){.len=12,.str="-show-y-axis"},
	(str_t){.len=3,.str="-sa"},
	(str_t){.len=10,.str="-show-axis"},
	(str_t){.len=4,.str="-sxf"},
	(str_t){.len=15,.str="-show-x-figures"},
	(str_t){.len=4,.str="-syf"},
	(str_t){.len=15,.str="-show-y-figures"},
	(str_t){.len=3,.str="-sf"},
	(str_t){.len=13,.str="-show-figures"},
};

str_t yes = (str_t){.len=3,.str="yes"};
str_t nay = (str_t){.len=3,.str="nay"};

int readArgs(int argc, char** argv){
	if(argc > 1){
		int bad = 0;
		for(int i = 1; i < argc; i++){
			int passed = 1;
			str_t a; str_tnew(&a,argv[i]);
			if(ARG(ARG_HELP)){
				help();
				return 1;
			}

			if(ARG(ARG_VERSION)){
				version();
				return 1;
			}

			if(ARG(ARG_INPUT)){
				for(int j = i + 1; j < argc; j++){
					str_t line;
					str_tnew(&line,argv[j]);
					eval(&line);
				}
				return 1;
			}

			if(ARG(ARG_HEIGHT)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					gHeight = str_ttoi(&b);
				}
				if(gHeight <= 0){ gHeight = 400; }
				setDisplaySize(&gDisplay,gHeight,gWitdh);
				passed = 0;
			}

			if(ARG(ARG_WITDH)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					gWitdh = str_ttoi(&b);
				}
				if(gWitdh <= 0){ gWitdh = 600; }
				setDisplaySize(&gDisplay,gHeight,gWitdh);
				passed = 0;
			}

			if(ARG(ARG_BORDER)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int border = str_ttoi(&b);
					setBorder(&gDisplay,border);
				}
				passed = 0;
			}

			if(ARG(ARG_BORDER_LEFT)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int border = str_ttoi(&b);
					setBorderLeft(&gDisplay,border);
				}
				passed = 0;
			}

			if(ARG(ARG_BORDER_RIGHT)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int border = str_ttoi(&b);
					setBorderRight(&gDisplay,border);
				}
				passed = 0;
			}

			if(ARG(ARG_BORDER_UP)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int border = str_ttoi(&b);
					setBorderUp(&gDisplay,border);
				}
				passed = 0;
			}

			if(ARG(ARG_BORDER_DOWN)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int border = str_ttoi(&b);
					setBorderDown(&gDisplay,border);
				}
				passed = 0;
			}

			if(ARG(ARG_BORDER_COLOR)){
				if(i + 3 < argc){
					str_t r; str_tnew(&r,argv[++i]);
					str_t g; str_tnew(&g,argv[++i]);
					str_t b; str_tnew(&b,argv[++i]);
					int cr = str_ttoi(&r);
					int cg = str_ttoi(&g);
					int cb = str_ttoi(&b);
					color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
					setBorderColor(&gDisplay,&c);
				}
				passed = 0;
			}

			if(ARG(ARG_LINE_COLOR)){
				if(i + 3 < argc){
					str_t r; str_tnew(&r,argv[++i]);
					str_t g; str_tnew(&g,argv[++i]);
					str_t b; str_tnew(&b,argv[++i]);
					int cr = str_ttoi(&r);
					int cg = str_ttoi(&g);
					int cb = str_ttoi(&b);
					color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
					setLineColor(&gDisplay,&c);
				}
				passed = 0;
			}

			if(ARG(ARG_AXIS_COLOR)){
				if(i + 3 < argc){
					str_t r; str_tnew(&r,argv[++i]);
					str_t g; str_tnew(&g,argv[++i]);
					str_t b; str_tnew(&b,argv[++i]);
					int cr = str_ttoi(&r);
					int cg = str_ttoi(&g);
					int cb = str_ttoi(&b);
					color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
					setAxisColor(&gDisplay,&c);
				}
				passed = 0;
			}

			if(ARG(ARG_CHAR_COLOR)){
				if(i + 3 < argc){
					str_t r; str_tnew(&r,argv[++i]);
					str_t g; str_tnew(&g,argv[++i]);
					str_t b; str_tnew(&b,argv[++i]);
					int cr = str_ttoi(&r);
					int cg = str_ttoi(&g);
					int cb = str_ttoi(&b);
					color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
					setCharColor(&gDisplay,&c);
				}
				passed = 0;
			}

			if(ARG(ARG_VIEW_COLOR)){
				if(i + 3 < argc){
					str_t r; str_tnew(&r,argv[++i]);
					str_t g; str_tnew(&g,argv[++i]);
					str_t b; str_tnew(&b,argv[++i]);
					int cr = str_ttoi(&r);
					int cg = str_ttoi(&g);
					int cb = str_ttoi(&b);
					color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
					setViewColor(&gDisplay,&c);
				}
				passed = 0;
			}

			if(ARG(ARG_X_START)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					float x = str_ttof(&b);
					setXstart(&gDisplay,x);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_START)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					float y = str_ttof(&b);
					setYstart(&gDisplay,y);
				}
				passed = 0;
			}

			if(ARG(ARG_X_END)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					float x = str_ttof(&b);
					setXend(&gDisplay,x);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_END)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					float y = str_ttof(&b);
					setYend(&gDisplay,y);
				}
				passed = 0;
			}

			if(ARG(ARG_X_RANGE)){
				if(i + 2 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					str_t c; str_tnew(&b,argv[++i]);
					float xs = str_ttof(&b);
					float xe = str_ttof(&c);
					setXrange(&gDisplay,xs,xe);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_RANGE)){
				if(i + 2 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					str_t c; str_tnew(&b,argv[++i]);
					float ys = str_ttof(&b);
					float ye = str_ttof(&c);
					setYrange(&gDisplay,ys,ye);
				}
				passed = 0;
			}

			if(ARG(ARG_X_PADDING)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					float x = str_ttof(&b);
					setXpad(&gDisplay,x);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_PADDING)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					float y = str_ttof(&b);
					setYpad(&gDisplay,y);
				}
				passed = 0;
			}

			if(ARG(ARG_X_LINES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int x = str_ttoi(&b);
					setXlines(&gDisplay,x);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_LINES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int y = str_ttoi(&b);
					setYlines(&gDisplay,y);
				}
				passed = 0;
			}

			if(ARG(ARG_X_LINES_SY)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int x = str_ttoi(&b);
					setXlinesSy(&gDisplay,x);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_LINES_SX)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int y = str_ttoi(&b);
					setYlinesSx(&gDisplay,y);
				}
				passed = 0;
			}

			if(ARG(ARG_CHAR_SIZE)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int s = str_ttoi(&b);
					setCharsize(&gDisplay,s);
				}
				passed = 0;
			}

			if(ARG(ARG_LINE_WIDTH)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int w = str_ttoi(&b);
					setLineWidth(&gDisplay,w);
				}
				passed = 0;
			}

			if(ARG(ARG_AXIS_LINE_WIDTH)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int w = str_ttoi(&b);
					setAxisLineWidth(&gDisplay,w);
				}
				passed = 0;
			}

			if(ARG(ARG_X_FIGURE_FORMAT)){
				if(i + 1 < argc){
					setXFigureFormat(&gDisplay,argv[++i]);
				}
				passed = 0;
			}

			if(ARG(ARG_Y_FIGURE_FORMAT)){
				if(i + 1 < argc){
					setYFigureFormat(&gDisplay,argv[++i]);
				}
				passed = 0;
			}

			if(ARG(ARG_FIGURE_FORMAT)){
				if(i + 1 < argc){
					setFigureFormat(&gDisplay,argv[++i]);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_X_LINES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}

					showXlines(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_Y_LINES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showYlines(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_LINES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showLines(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_DASHED_LINE)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					dashedLine(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_X_AXIS)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showXAxis(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_Y_AXIS)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showYAxis(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_AXIS)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showAxis(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_X_FIGURES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showXFigures(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_Y_FIGURES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showYlines(&gDisplay,l);
				}
				passed = 0;
			}

			if(ARG(ARG_SHOW_FIGURES)){
				if(i + 1 < argc){
					str_t b; str_tnew(&b,argv[++i]);
					int l = str_ttoi(&b);
					if(str_tequ(&b,&yes)){
						l = 1;
					}
					if(str_tequ(&b,&nay)){
						l = 0;
					}
					
					showFigures(&gDisplay,l);
				}
				passed = 0;
			}


			// default
			if(passed){
				badArg(&a,bad);
				bad = 1;
			}
		}
	}

	return 0;
}

#endif
