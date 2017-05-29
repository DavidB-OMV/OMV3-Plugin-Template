<?php

class OMVModuleExample extends \OMV\Engine\Module\ServiceAbstract
    implements \OMV\Engine\Notify\IListener
{
    public function getName()
    {
        return "example";
    }

    public function applyConfig()
    {
        $cmd = new \OMV\System\Process("omv-mkconf", "example");
        $cmd->setRedirect2to1();
        $cmd->execute();
    }

    public function bindListeners(\OMV\Engine\Notify\Dispatcher $dispatcher)
    {
        $dispatcher->addListener(
            OMV_NOTIFY_MODIFY,
            "org.openmediavault.conf.service.example",
            [ $this, "setDirty" ]
        );
    }
}
