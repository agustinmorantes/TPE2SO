#include <io.h>
#include <stdarg.h>
#include <stdint.h>
#include <str.h>
#include <syscall.h>

#define BUFFER_SIZE 1000

// buffer para usar en la conversion de numero a string 20 digitos es lo maximo que podria tener un numero
static char numtostrbuffer[64];

static char buffer[BUFFER_SIZE];

int parseFormat(const char * format, va_list args) {
    int found_percentage = 0;
    int i, j, aux;

    for (i = 0, j = 0; format[i] != 0; i++)
    {
        if (!found_percentage && format[i] == '%'  )
        {
            found_percentage = 1;
            continue;
        }

        if (found_percentage)
        {
            switch (format[i])
            {
            case '%':
                buffer[j++] = format[i];
                found_percentage = 0;
                break;
            case 'd':
                aux = (int) va_arg(args,int);
                if (aux < 0) {
                    aux *= -1;
                    buffer[j++] = '-';
                }
                uintToBase(aux,numtostrbuffer,10);
                j += strcpy(&buffer[j],numtostrbuffer);
                found_percentage = 0;
                break;
            case 's':
                j += strcpy(&buffer[j],va_arg(args,char *));
                found_percentage = 0;
                break;
            case 'c':
                buffer[j++] = va_arg(args,int);
                found_percentage = 0;
                break;
            case 'x':
                uintToBase(va_arg(args,int),numtostrbuffer,16);
                j += strcpy(&buffer[j],numtostrbuffer);
                found_percentage = 0;
                break;
            case 'f':  
                floatToStr(va_arg(args,double),numtostrbuffer,6);
                j += strcpy(&buffer[j],numtostrbuffer);
                found_percentage = 0;
                break;
            default:
                buffer[j] = 0;
                return j;
            }
        }
        else 
        {
            buffer[j++] = format[i];
        }
    }
    
    buffer[j] = 0;
    return j;
}

int scan(const char * format, va_list args) {
    int found_percentage = 0;
    int count = 0;
    int j = 0;
    int width = 0, len = 0;
    int read = _sysread(0,buffer,BUFFER_SIZE);

    for (int i = 0; format[i] != 0; i++)
    {   
        if (found_percentage)
        {
            while (isWhitespace(buffer[j]) && j < read)
                j++;

            while (j >= read)
                read += _sysread(0,&buffer[j],BUFFER_SIZE);

            if (isNumber(format[i]))
                i += strToIntBase(&format[i],-1,10,&width,1); // -1 en len significa que lee hasta que se cumpla otra condicion

            len = (width == 0 || (read - j) < width) ? (read - j) : width;
            
            switch (format[i])
            {
            case 'd':
                j += strToIntBase(&buffer[j], len, 10, (int *) va_arg(args, int *),0);
                found_percentage = 0;
                width = 0;
                count++;
                break;
            case 's':
                j += strncpy((char *) va_arg(args,char *),&buffer[j], len) - 1;
                found_percentage = 0;
                width = 0;
                count++;
                break;
            case 'c':
                *(char *) va_arg(args,char *) = buffer[j];
                j += width == 0 ? 1 : width;
                found_percentage = 0;
                width = 0;
                count++;
                break;
            case 'x':
                j += strToIntBase(&buffer[j], len, 16, (int *) va_arg(args, int *),0);
                found_percentage = 0;
                width = 0;
                count++;
                break;
            case 'f':
                j += strToFloat(&buffer[j], len, (double *) va_arg(args, double *));
                found_percentage = 0;
                width = 0;
                count++;
                break;
            default:
                return count;
            }
        } 
        else 
        {
            if (format[i] == '%')
                found_percentage = 1;
            else if (format[i] == buffer[j])
                j++;
            else if (!isWhitespace(format[i]))
            {
                return count;
            }   
        }
    }
    return count;
}

int printf(const char * format, ...) {
    va_list args;
    va_start(args,format);
    int lenght = parseFormat(format,args);
    va_end(args);
    return _syswrite(1, buffer, lenght);
}

int scanf(const char * format, ...) {
    va_list args;
    va_start(args, format);
    int num_readed = scan(format, args);
    va_end(args);
    return num_readed;
}

int getchar() {
    static char getBuff[BUFFER_SIZE];
    static int i = 0, read = 0;
    
    if (read == i)
    {
        i = 0;
        if  ((read = _sysread(0,getBuff,BUFFER_SIZE)) < 0)
            return -1;
    }
    return getBuff[i++];
}

int putchar(char c) {
    if  (_syswrite(1,&c,1) < 0) {
        return -1;
    }
    return c;
}

void clearTerminal() {
    _sysclear();
}
