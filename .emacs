(load-file "~/tools/cedet-1.1/common/cedet.el")
(load-file "~/tools/cedet-1.1/semantic/bovine/semantic-gcc.el")
(load-file "~/tools/cedet-1.1/semantic/bovine/semantic-c.el")
(semantic-load-enable-minimum-features)
(semantic-load-enable-code-helpers)
(semantic-load-enable-guady-code-helpers)
(semantic-load-enable-excessive-code-helpers)
(semantic-load-enable-semantic-debugging-helpers)

(setq make-backup-files nil)

;;Include settings
;;(require 'semantic/bovine/semantic-gcc.el)
;;(require 'semantic/bovine/semantic-c.el)

(global-linum-mode 'linum-mode)

;;bind key
(global-set-key [f12] 'semantic-ia-fast-jump)

(defun my-cedet-hook()
(local-set-key (kbd "M-n") 'semantic-ia-complete-symbol)
)
(add-hook 'c-mode-common-hook 'my-cedet-hook)