((c-mode . ((eval . (setq-local c-macro-cppflags
                                  (concat "-ffreestanding -mno-red-zone "
                                          "-I" (expand-file-name "source/include/" (locate-dominating-file default-directory ".dir-locals.el"))
                                          " -I" (expand-file-name "source/libc/include/" (locate-dominating-file default-directory ".dir-locals.el"))
																	)
										)
					  ))
))
