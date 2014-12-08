;Here is the script
(define (script-fu-gds-save-layers img drw filename)
(let*
(
(num-layer (car (gimp-image-get-layers img)))
(layers (cadr (gimp-image-get-layers img)))
(index 0)
(basename (unbreakupstr (butlast (strbreakup
filename ".")) "."))
(extension (car (last (strbreakup filename "."))))
(layer)
(filename)
)
(while (< index num-layer)
(gimp-drawable-set-visible (aref layers index)
FALSE)
(set! index (+ index 1))
)
(set! index 0)
(while (< index num-layer)
(set! layer (aref layers index))
(gimp-drawable-set-visible layer TRUE)
(set! filename (string-append basename (car
(gimp-drawable-get-name layer)) "." extension))
(gimp-file-save RUN-NONINTERACTIVE img layer
filename filename)
(gimp-drawable-set-visible layer FALSE)
(set! index (+ index 1))
)

(set! index 0)
(while (< index num-layer)
(gimp-drawable-set-visible (aref layers index)
TRUE)
(set! index (+ index 1))
)

)
)

(script-fu-register "script-fu-gds-save-layers"
"<Image>/Script-Fu/Utils/Save layers..."
"Save each layer of an image individually" ;comment
"G. de Sercey" ;author
"Gd32@..." ;copyright
"June 2003" ;date
"*A"
SF-IMAGE "img" 0
SF-DRAWABLE "drw" 0
SF-FILENAME "destination" ""
)