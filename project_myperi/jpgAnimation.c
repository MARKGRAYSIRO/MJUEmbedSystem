#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "libfbdev.h"
#include "jpeglib.h"
#include "jpgAnimation.h"

void jpg_play(char *filename){
	int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;

	if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
	}
	//Clear FB.
	fb_clear();
	
	int i=0;
	
		usleep(10);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;
		int currPoint =0;
		data = malloc(cols*rows*3);
		
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);
}

void* read_jpg_start(void*arg)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;

	if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
	}
	//Clear FB.
	fb_clear();
	
	int i=0;
	for (i=0; i<=60 ;i++)
	{ 
		usleep(10);
		char filename[200]={0,};
		snprintf(filename,200,"./startimage/c443084dcda64f79b561de8037a5ac034B78XvhapWdl2Gan-%d.jpeg",i*2);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);
	
	}
		pthread_exit(NULL);
	}
	



	/*
	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		
		
	}
	//Clear FB.
	fb_clear();
	
	int i=1;
	while(1) {

	switch(flag){
	case 49995: // left
	for (i=345; i<=364;i++)
	{ 
		char filename[200]={0,};
		snprintf(filename,200,"./image/s%05d.jpg",i);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);
		fail = 1;
	   }
	   
	  
	  break; 
	 case 50000: // right 
	 for (i=591; i<=609;i++)
	{ 
		char filename[200]={0,};
		snprintf(filename,200,"./image/s%05d.jpg",i);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);
		fail = 1;
	   }
	 
	 
	 
	 
	 
	
	 case 50005: //strike
	 for (i=966; i<=994;i++)
	{ 
		char filename[200]={0,};
		snprintf(filename,200,"./image/s%05d.jpg",i);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);

	   }
	 
	 break;
	 default:	 
	
	
	{    // flag 에 자이로 리턴값 멕여 여기서 
		
		char filename[200]={0,};
		snprintf(filename,200,"./image/d_%d.jpg",num);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);
		
		if (flag > 200) { num -- ;}
		else if (flag < -200) { num++; }
		
		if(num < 0 || num > 11){
			num == 6;
			
			
			
			}
		 break;
	   }
	 
	} 
}
	fb_close();

}
*/